/* klog.c - Structured kernel logging with levels and subsystems.
 *
 * Provides klog() with level/subsystem filtering, and klog_hexdump()
 * for binary data inspection.  Replaces raw kprintf calls in new code;
 * existing kprintf calls are left untouched for backward compatibility.
 *
 * Usage:
 *   klog(LOG_INFO, SUBSYS_MM, "heap at 0x%lx, %lu bytes", base, size);
 *   klog_hexdump(LOG_DEBUG, SUBSYS_NET, buf, 64, "RX frame");
 */

#include "kernel.h"

static const char *level_names[] = {
    "EMERG", "ALERT", "CRIT", "ERR", "WARN", "NOTICE", "INFO", "DEBUG"
};

static const char *subsys_names[] = {
    "MM", "SCHED", "VFS", "NET", "DRIVER", "SYSCALL", "SHELL", "BOOT", "GENERAL"
};

/* Current filtering thresholds (global and per-subsystem). */
static log_level_t global_max_level = LOG_DEBUG;
static log_level_t subsys_max_level[LOG_SUBSYS_COUNT];

/* Set by boot or command line; when nonzero, klog() is silent. */
static int klog_disabled;

void klog_set_level(log_level_t level) {
    global_max_level = level;
}

void klog_set_subsys_level(log_subsystem_t subsys, log_level_t level) {
    if (subsys < LOG_SUBSYS_COUNT)
        subsys_max_level[subsys] = level;
}

void klog_disable(void) { klog_disabled = 1; }
void klog_enable(void)  { klog_disabled = 0; }

void klog(log_level_t level, log_subsystem_t subsys,
          const char *fmt, ...) {
    if (klog_disabled) return;
    if (level > global_max_level) return;
    if (subsys < LOG_SUBSYS_COUNT && level > subsys_max_level[subsys])
        return;

    /* Prefix: [LEVEL SUBSYS] */
    const char *lname = (level <= LOG_DEBUG) ? level_names[level] : "???";
    const char *sname = (subsys < LOG_SUBSYS_COUNT)
                        ? subsys_names[subsys] : "???";
    kprintf("[%s %s] ", lname, sname);

    /* Format the user message. */
    __builtin_va_list ap;
    __builtin_va_start(ap, fmt);
    /* Reuse kprintf's internal formatter via a wrapper. */
    char buf[512];
    int pos = 0;
    const char *p;
    for (p = fmt; *p && pos < (int)sizeof(buf) - 1; p++) {
        if (*p != '%') { buf[pos++] = *p; continue; }
        p++;
        if (*p == 0) break;
        if (*p == 's') {
            const char *s = __builtin_va_arg(ap, const char *);
            if (!s) s = "(null)";
            while (*s && pos < (int)sizeof(buf) - 1) buf[pos++] = *s++;
        } else if (*p == 'd' || *p == 'i') {
            int v = __builtin_va_arg(ap, int);
            char tmp[12]; int t = 0;
            if (v < 0) { buf[pos++] = '-'; v = -v; }
            if (v == 0) { buf[pos++] = '0'; }
            else { while (v > 0) { tmp[t++] = '0' + v % 10; v /= 10; } }
            while (t > 0) buf[pos++] = tmp[--t];
        } else if (*p == 'u') {
            unsigned v = __builtin_va_arg(ap, unsigned);
            char tmp[12]; int t = 0;
            if (v == 0) { buf[pos++] = '0'; }
            else { while (v > 0) { tmp[t++] = '0' + v % 10; v /= 10; } }
            while (t > 0) buf[pos++] = tmp[--t];
        } else if (*p == 'x' || *p == 'X') {
            unsigned long v = __builtin_va_arg(ap, unsigned long);
            const char *hex = "0123456789abcdef";
            char tmp[16]; int t = 0;
            if (v == 0) { buf[pos++] = '0'; }
            else { while (v > 0) { tmp[t++] = hex[v & 0xF]; v >>= 4; } }
            while (t > 0) buf[pos++] = tmp[--t];
        } else if (*p == 'l' && (p[1] == 'd' || p[1] == 'x')) {
            char spec = *++p;
            long v = __builtin_va_arg(ap, long);
            if (spec == 'x') {
                const char *hex = "0123456789abcdef";
                char tmp[16]; int t = 0;
                if (v == 0) { buf[pos++] = '0'; }
                else { unsigned long uv = (unsigned long)v;
                       while (uv > 0) { tmp[t++] = hex[uv & 0xF]; uv >>= 4; } }
                while (t > 0) buf[pos++] = tmp[--t];
            } else {
                if (v < 0) { buf[pos++] = '-'; v = -v; }
                if (v == 0) { buf[pos++] = '0'; }
                else { char tmp[20]; int t = 0;
                       while (v > 0) { tmp[t++] = '0' + v % 10; v /= 10; }
                       while (t > 0) buf[pos++] = tmp[--t]; }
            }
        } else if (*p == 'c') {
            buf[pos++] = (char)__builtin_va_arg(ap, int);
        } else {
            buf[pos++] = '%';
            buf[pos++] = *p;
        }
    }
    buf[pos] = '\0';
    __builtin_va_end(ap);

    kprintf("%s\n", buf);
}

void klog_hexdump(log_level_t level, log_subsystem_t subsys,
                  const void *data, unsigned long len, const char *label) {
    if (klog_disabled) return;
    if (level > global_max_level) return;
    if (subsys < LOG_SUBSYS_COUNT && level > subsys_max_level[subsys])
        return;

    const char *lname = (level <= LOG_DEBUG) ? level_names[level] : "???";
    const char *sname = (subsys < LOG_SUBSYS_COUNT)
                        ? subsys_names[subsys] : "???";
    const unsigned char *p = (const unsigned char *)data;

    kprintf("[%s %s] %s (%lu bytes):\n", lname, sname, label, len);
    for (unsigned long i = 0; i < len; i += 16) {
        kprintf("  %04lx: ", i);
        /* Hex bytes */
        for (unsigned long j = 0; j < 16 && i + j < len; j++)
            kprintf("%02x ", p[i + j]);
        /* Pad if last row is short */
        for (unsigned long j = len - i; j < 16; j++)
            kprintf("   ");
        /* ASCII */
        kprintf(" |");
        for (unsigned long j = 0; j < 16 && i + j < len; j++) {
            unsigned char c = p[i + j];
            kprintf("%c", (c >= 32 && c < 127) ? c : '.');
        }
        kprintf("|\n");
    }
}
