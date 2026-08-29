/* MiniOS QEMU guest agent (QGA).
 *
 * Speaks the QEMU guest agent protocol over a dedicated ISA serial port
 * (COM2) that the host maps to a socket chardev. The host drives a booted
 * MiniOS without a user at the console: tools/qga_client.py connects to the
 * socket, sends one JSON object per line, and reads the JSON reply. The
 * framing is whitespace-delimited, so QEMU's own QMP guest-agent-command can
 * drive the same channel.
 *
 * Polled channel (no interrupt controller): qga_init sets up COM2 and
 * qga_poll, called from raw_blocking_getc, services one complete line per
 * call. Every input path is bounded and fail-closed: a malformed, overlong or
 * nested-too-deep request is rejected with an error reply, never accepted.
 */

#include "kernel.h"
#include "qga.h"
#include "rtc.h"

static void qga_puts_resp(void);
static void qga_resp_putc_enc(char c);

/* ================================================================
 *  COM2 UART
 * ================================================================ */

static int qga_tx_ready(void) { return inb(QGA_COM2_BASE + QGA_UART_LSR) & QGA_UART_LSR_TX_RDY; }
static int qga_rx_ready(void) { return inb(QGA_COM2_BASE + QGA_UART_LSR) & QGA_UART_LSR_RX_RDY; }

static void qga_putc(char c) {
    while (!qga_tx_ready());
    outb(QGA_COM2_BASE + QGA_UART_THR, (unsigned char)c);
}

void qga_init(void) {
    outb(QGA_COM2_BASE + QGA_UART_IER, 0x00);                 /* no interrupts */
    outb(QGA_COM2_BASE + QGA_UART_LCR, QGA_UART_LCR_DLAB);    /* DLAB on */
    outb(QGA_COM2_BASE + QGA_UART_DLL, QGA_BAUD_DIVISOR);     /* divisor lo */
    outb(QGA_COM2_BASE + QGA_UART_DLM, 0x00);                 /* divisor hi */
    outb(QGA_COM2_BASE + QGA_UART_LCR, QGA_UART_LCR_8N1);     /* 8N1 */
    outb(QGA_COM2_BASE + QGA_UART_FCR, QGA_UART_FCR_CFG);     /* FIFO on */
    outb(QGA_COM2_BASE + QGA_UART_MCR, QGA_UART_MCR_CFG);     /* RTS/DSR */
}

/* ================================================================
 *  JSON flat parser
 * ================================================================ */

struct qga_pair {
    char key[QGA_KEY_MAX];
    char type;              /* 'S' string, 'I' int, 'N' null, 'B' bool */
    char str[QGA_STR_MAX];
    long ival;
};

static int qga_ws(char c) {
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

/* Parse a JSON object whose members are stored flat into out[*count..]: a
 * nested object's members keep the parent key as a prefix (`arguments.id`).
 * Only string/int/null/bool values are accepted; arrays and deeper nesting
 * are rejected fail-closed. Returns 1 on success, 0 on malformed or
 * overflowing input. */
static int qga_parse_object(const char **pp, struct qga_pair *out, int max,
                            int *count, const char *prefix, int depth) {
    const char *p = *pp;
    if (*p != '{') return 0;
    p++;
    for (;;) {
        while (qga_ws(*p)) p++;
        if (*p == '}') { p++; break; }
        if (*p != '"') return 0;
        p++;
        char key[QGA_KEY_MAX];
        int kl = 0;
        while (*p && *p != '"' && kl < QGA_KEY_MAX - 1) key[kl++] = *p++;
        if (*p != '"') return 0;
        key[kl] = 0;
        p++;
        while (qga_ws(*p)) p++;
        if (*p != ':') return 0;
        p++;
        while (qga_ws(*p)) p++;

        if (*p == '{') {
            if (depth <= 0) return 0;
            char np[QGA_KEY_MAX];
            if (prefix[0]) ksnprintf(np, sizeof(np), "%s.%s", prefix, key);
            else kstrcpy(np, key);
            if (kstrlen(np) >= QGA_KEY_MAX) return 0;
            /* qga_parse_object consumes the leading '{' itself, so p is
             * passed pointing at it (matching the top-level call). */
            if (!qga_parse_object(&p, out, max, count, np, depth - 1)) return 0;
        } else {
            if (*count >= max) return 0;
            struct qga_pair *e = &out[(*count)++];
            if (prefix[0]) ksnprintf(e->key, sizeof(e->key), "%s.%s", prefix, key);
            else kstrcpy(e->key, key);
            if (kstrlen(e->key) >= QGA_KEY_MAX) return 0;
            if (*p == '"') {
                p++;
                int sl = 0;
                while (*p && *p != '"' && sl < QGA_STR_MAX - 1) e->str[sl++] = *p++;
                if (*p != '"') return 0;
                e->str[sl] = 0;
                p++;
                e->type = 'S';
            } else if (*p == '-' || (*p >= '0' && *p <= '9')) {
                long v = 0;
                int neg = 0;
                if (*p == '-') { neg = 1; p++; }
                if (!(*p >= '0' && *p <= '9')) return 0;
                while (*p >= '0' && *p <= '9') {
                    v = v * 10 + (*p - '0');
                    if (v < 0) return 0;               /* overflow */
                    p++;
                }
                e->ival = neg ? -v : v;
                e->type = 'I';
            } else if (kstrncmp(p, "null", 4) == 0) {
                p += 4;
                e->type = 'N';
            } else if (kstrncmp(p, "true", 4) == 0) {
                p += 4;
                e->type = 'B';
                e->ival = 1;
            } else if (kstrncmp(p, "false", 5) == 0) {
                p += 5;
                e->type = 'B';
                e->ival = 0;
            } else {
                return 0;
            }
        }
        while (qga_ws(*p)) p++;
        if (*p == ',') { p++; continue; }
        if (*p == '}') { p++; break; }
        return 0;
    }
    *pp = p;
    return 1;
}

/* Parse a request line into the flat pair table. Returns the number of pairs,
 * or -1 on malformed/overflowing input. */
static int qga_parse_flat(const char *s, struct qga_pair *out, int max) {
    const char *p = s;
    int count = 0;
    while (qga_ws(*p)) p++;
    if (*p != '{') return -1;
    if (!qga_parse_object(&p, out, max, &count, "", QGA_MAX_DEPTH)) return -1;
    while (qga_ws(*p)) p++;
    if (*p != 0) return -1;              /* trailing junk after the object */
    return count;
}

static const char *qga_get_str(const struct qga_pair *pairs, int n, const char *key) {
    int i;
    for (i = 0; i < n; i++)
        if (pairs[i].type == 'S' && kstrcmp(pairs[i].key, key) == 0)
            return pairs[i].str;
    return 0;
}

static int qga_get_int(const struct qga_pair *pairs, int n, const char *key, long *out) {
    int i;
    for (i = 0; i < n; i++)
        if (pairs[i].type == 'I' && kstrcmp(pairs[i].key, key) == 0) {
            *out = pairs[i].ival;
            return 1;
        }
    return 0;
}

/* ================================================================
 *  Response writer
 * ================================================================ */

static char qga_resp[QGA_RESP_MAX];
static int  qga_resp_len;
static int  qga_sync_pending;           /* guest-sync-delimited: 0xFF first */

static void qga_resp_reset(void) { qga_resp_len = 0; qga_resp[0] = 0; qga_sync_pending = 0; }

static void qga_resp_puts(const char *s) {
    while (*s) {
        if (qga_resp_len < QGA_RESP_MAX - 1) qga_resp[qga_resp_len++] = *s;
        s++;
    }
    qga_resp[qga_resp_len] = 0;
}

static void qga_resp_putc_enc(char c) {
    if (qga_resp_len < QGA_RESP_MAX - 1) qga_resp[qga_resp_len++] = c;
    qga_resp[qga_resp_len] = 0;
}

/* Append the decimal form of v (a separate helper so no varargs forwarding is
 * needed; the kernel formatter is not re-entrant with a stored va_list). */
static void qga_resp_put_long(long v) {
    char buf[24];
    int pos = 0;
    if (v < 0) { qga_resp_putc_enc('-'); v = -v; }
    if (v == 0) buf[pos++] = '0';
    while (v > 0 && pos < 23) { buf[pos++] = '0' + (int)(v % 10); v /= 10; }
    while (pos > 0) qga_resp_putc_enc(buf[--pos]);
}

static void qga_err(const char *klass, const char *desc) {
    qga_resp_puts("{\"error\":{\"class\":\"");
    qga_resp_puts(klass);
    qga_resp_puts("\",\"desc\":\"");
    qga_resp_puts(desc);
    qga_resp_puts("\"}}");
}

static void qga_puts_resp(void) {
    int i;
    for (i = 0; i < qga_resp_len; i++) qga_putc(qga_resp[i]);
    qga_putc('\n');
}

/* ================================================================
 *  Base64
 * ================================================================ */

static const char qga_b64[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static void qga_b64_encode(const unsigned char *in, int n) {
    int i = 0;
    while (i + 3 <= n) {
        unsigned long x = ((unsigned long)in[i] << 16) | ((unsigned long)in[i + 1] << 8) | in[i + 2];
        qga_resp_putc_enc(qga_b64[(x >> 18) & 0x3F]);
        qga_resp_putc_enc(qga_b64[(x >> 12) & 0x3F]);
        qga_resp_putc_enc(qga_b64[(x >> 6) & 0x3F]);
        qga_resp_putc_enc(qga_b64[x & 0x3F]);
        i += 3;
    }
    if (i + 2 == n) {
        unsigned long x = ((unsigned long)in[i] << 16) | ((unsigned long)in[i + 1] << 8);
        qga_resp_putc_enc(qga_b64[(x >> 18) & 0x3F]);
        qga_resp_putc_enc(qga_b64[(x >> 12) & 0x3F]);
        qga_resp_putc_enc(qga_b64[(x >> 6) & 0x3F]);
        qga_resp_putc_enc('=');
    } else if (i + 1 == n) {
        unsigned long x = (unsigned long)in[i] << 16;
        qga_resp_putc_enc(qga_b64[(x >> 18) & 0x3F]);
        qga_resp_putc_enc(qga_b64[(x >> 12) & 0x3F]);
        qga_resp_putc_enc('=');
        qga_resp_putc_enc('=');
    }
}

/* ================================================================
 *  Commands
 * ================================================================ */

static const char qga_info_json[] =
    "{\"return\":{\"version\":\"miniOS-guest-agent-0.1\","
    "\"supported_commands\":["
    "{\"enabled\":true,\"name\":\"guest-file-close\"},"
    "{\"enabled\":true,\"name\":\"guest-file-open\"},"
    "{\"enabled\":true,\"name\":\"guest-file-read\"},"
    "{\"enabled\":true,\"name\":\"guest-exec\"},"
    "{\"enabled\":true,\"name\":\"guest-get-host-name\"},"
    "{\"enabled\":true,\"name\":\"guest-get-osinfo\"},"
    "{\"enabled\":true,\"name\":\"guest-get-time\"},"
    "{\"enabled\":true,\"name\":\"guest-info\"},"
    "{\"enabled\":true,\"name\":\"guest-ping\"},"
    "{\"enabled\":true,\"name\":\"guest-shutdown\"},"
    "{\"enabled\":true,\"name\":\"guest-sync\"},"
    "{\"enabled\":true,\"name\":\"guest-sync-delimited\"}"
    "]}}";

static const char qga_osinfo_json[] =
    "{\"return\":{\"kernel-release\":\"v0.3\","
    "\"kernel-version\":\"MiniOS\",\"machine\":\"x86_64\"}}";

static void qga_cmd_get_time(void) {
    int y, mo, d, h, mi, s;
    long days, epoch;
    if (!rtc_read_datetime(&y, &mo, &d, &h, &mi, &s)) {
        qga_err("GenericError", "rtc unavailable");
        return;
    }
    /* days_from_civil (Howard Hinnant): day number since 1970-01-01. */
    y -= (mo <= 2);
    {
        long era = (y >= 0 ? (long)y : (long)y - 399) / 400;
        long yoe = (long)y - era * 400;
        long doy = (153 * ((long)mo + (mo > 2 ? -3 : 9)) + 2) / 5 + (long)d - 1;
        long doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
        days = era * 146097 + doe - 719468;
    }
    epoch = days * 86400L + (long)h * 3600 + (long)mi * 60 + (long)s;
    qga_resp_puts("{\"return\":");
    qga_resp_put_long(epoch);
    qga_resp_puts("}");
}

/* guest-exec runs a shell command line; output goes to the console (the `>`
 * redirect still captures it). Queued so the shell executes it at its next
 * loop top, which raw_blocking_getc forces by returning a newline. */
static void qga_cmd_exec(const struct qga_pair *pairs, int n) {
    const char *path = qga_get_str(pairs, n, "arguments.path");
    if (!path || !path[0]) {
        qga_err("GenericError", "missing path");
        return;
    }
    shell_queue_launch(path);
    qga_resp_puts("{\"return\":{\"pid\":0}}");
}

static void qga_cmd_shutdown(const struct qga_pair *pairs, int n) {
    const char *mode = qga_get_str(pairs, n, "arguments.mode");
    (void)mode;                          /* MiniOS has one poweroff path */
    qga_resp_puts("{\"return\":{}}");
}

/* ================================================================
 *  guest-file-* : ramdisk file I/O over integer handles
 * ================================================================ */

static KFILE *qga_files[QGA_FILE_MAX];
static int    qga_files_used[QGA_FILE_MAX];

static int qga_file_size(const KFILE *f) {
    if (f->minifs_ino >= 0) return (int)f->minifs_size;
    return (int)f->rf->size;
}

static void qga_cmd_file_open(const struct qga_pair *pairs, int n) {
    const char *path = qga_get_str(pairs, n, "arguments.path");
    const char *mode = qga_get_str(pairs, n, "arguments.mode");
    int handle;
    if (!path || !path[0]) {
        qga_err("GenericError", "missing path");
        return;
    }
    for (handle = 0; handle < QGA_FILE_MAX; handle++)
        if (!qga_files_used[handle]) break;
    if (handle >= QGA_FILE_MAX) {
        qga_err("GenericError", "no free handle");
        return;
    }
    KFILE *f = kfopen(path, mode && mode[0] ? mode : "r");
    if (!f) {
        qga_err("GenericError", "cannot open");
        return;
    }
    qga_files[handle] = f;
    qga_files_used[handle] = 1;
    qga_resp_puts("{\"return\":");
    qga_resp_put_long((long)handle);
    qga_resp_puts("}");
}

static void qga_cmd_file_read(const struct qga_pair *pairs, int n) {
    long handle = 0, count = 0;
    unsigned char buf[QGA_FILE_READ_MAX];
    if (!qga_get_int(pairs, n, "arguments.handle", &handle) ||
        handle < 0 || handle >= QGA_FILE_MAX || !qga_files_used[handle]) {
        qga_err("GenericError", "bad handle");
        return;
    }
    qga_get_int(pairs, n, "arguments.count", &count);
    KFILE *f = qga_files[handle];
    int remaining = qga_file_size(f) - (int)f->pos;
    int want = (int)(count > 0 ? count : 0);
    int to_read = remaining < want ? remaining : want;
    if (to_read > QGA_FILE_READ_MAX) to_read = QGA_FILE_READ_MAX;
    if (to_read < 0) to_read = 0;
    int got = (int)kfread(buf, 1, (unsigned long)to_read, f);
    if (got < 0) got = 0;
    qga_resp_puts("{\"return\":{\"base64\":\"");
    qga_b64_encode(buf, got);
    qga_resp_puts("\",\"count\":");
    qga_resp_put_long((long)got);
    qga_resp_puts("}}");
}

static void qga_cmd_file_close(const struct qga_pair *pairs, int n) {
    long handle = 0;
    if (!qga_get_int(pairs, n, "arguments.handle", &handle) ||
        handle < 0 || handle >= QGA_FILE_MAX || !qga_files_used[handle]) {
        qga_err("GenericError", "bad handle");
        return;
    }
    kfclose(qga_files[handle]);
    qga_files_used[handle] = 0;
    qga_files[handle] = 0;
    qga_resp_puts("{\"return\":{}}");
}

/* ================================================================
 *  Dispatch + poll
 * ================================================================ */

static void qga_dispatch(struct qga_pair *pairs, int n) {
    const char *execute = qga_get_str(pairs, n, "execute");
    if (!execute) {
        qga_err("GenericError", "missing execute");
        return;
    }
    if (kstrcmp(execute, "guest-ping") == 0)
        qga_resp_puts("{\"return\":{}}");
    else if (kstrcmp(execute, "guest-info") == 0)
        qga_resp_puts(qga_info_json);
    else if (kstrcmp(execute, "guest-get-osinfo") == 0)
        qga_resp_puts(qga_osinfo_json);
    else if (kstrcmp(execute, "guest-get-host-name") == 0)
        qga_resp_puts("{\"return\":{\"host-name\":\"miniOS\"}}");
    else if (kstrcmp(execute, "guest-get-time") == 0)
        qga_cmd_get_time();
    else if (kstrcmp(execute, "guest-sync") == 0) {
        long id = 0;
        qga_get_int(pairs, n, "arguments.id", &id);
        qga_resp_puts("{\"return\":");
        qga_resp_put_long(id);
        qga_resp_puts("}");
    } else if (kstrcmp(execute, "guest-sync-delimited") == 0) {
        long id = 0;
        qga_get_int(pairs, n, "arguments.id", &id);
        qga_sync_pending = 1;
        qga_resp_puts("{\"return\":");
        qga_resp_put_long(id);
        qga_resp_puts("}");
    } else if (kstrcmp(execute, "guest-exec") == 0)
        qga_cmd_exec(pairs, n);
    else if (kstrcmp(execute, "guest-shutdown") == 0)
        qga_cmd_shutdown(pairs, n);
    else if (kstrcmp(execute, "guest-file-open") == 0)
        qga_cmd_file_open(pairs, n);
    else if (kstrcmp(execute, "guest-file-read") == 0)
        qga_cmd_file_read(pairs, n);
    else if (kstrcmp(execute, "guest-file-close") == 0)
        qga_cmd_file_close(pairs, n);
    else
        qga_err("CommandNotFound", execute);
}

/* Accumulate bytes until a complete line, then parse and answer it. Callers
 * call it once per idle spin of the shell's raw input loop. */
void qga_poll(void) {
    static char line[QGA_LINE_MAX];
    static int  len = 0;
    while (qga_rx_ready()) {
        char c = (char)inb(QGA_COM2_BASE + QGA_UART_RBR);
        if (c == '\n' || c == '\r') {
            if (len > 0) {
                line[len] = 0;
                struct qga_pair pairs[QGA_MAX_PAIRS];
                int n = qga_parse_flat(line, pairs, QGA_MAX_PAIRS);
                qga_resp_reset();
                if (n < 0)
                    qga_err("GenericError", "malformed request");
                else
                    qga_dispatch(pairs, n);
                if (qga_sync_pending) qga_putc((char)0xFF);
                qga_puts_resp();
            }
            len = 0;
        } else if (len < QGA_LINE_MAX - 1) {
            line[len++] = c;
        } else {
            len = 0;                       /* overlong: discard the line */
        }
    }
}
