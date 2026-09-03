#include "kernel.h"
#include "minifs.h"

/* ================================================================
 *  KFILE — Buffered file I/O over ramdisk and MiniFS
 * ================================================================ */

static KFILE  console_in  = { 0, 0, 0, 0, 0, 0, 1 };
static KFILE  console_out = { 0, 0, 0, 0, 0, 0, 1 };
static KFILE  console_err = { 0, 0, 0, 0, 0, 0, 1 };
KFILE *kstdin  = &console_in;
KFILE *kstdout = &console_out;
KFILE *kstderr = &console_err;

KFILE *kfile_stdin(void)  { return kstdin; }
KFILE *kfile_stdout(void) { return kstdout; }
KFILE *kfile_stderr(void) { return kstderr; }

KFILE *kfopen(const char *path, const char *mode) {
    char resolved[RAMDISK_FNAME_LEN];
    int want_write;
    if (!fs_resolve(path, resolved, sizeof(resolved))) return 0;
    if (fs_is_dir(resolved)) return 0;
    KFILE *f = kmalloc(sizeof(KFILE));
    if (!f) return 0;
    kmemset(f, 0, sizeof(KFILE));
    f->minifs_ino = -1;
    want_write = (mode[0] == 'w' || mode[0] == 'a');

    f->rf = ramdisk_open(resolved);
    if (!f->rf && want_write) {
        const char *slash = resolved + kstrlen(resolved);
        while (slash > resolved && slash[-1] != '/') slash--;
        int parent_ok = 1;
        if (slash != resolved && slash[-1] == '/') {
            char parent[RAMDISK_FNAME_LEN];
            unsigned plen = (unsigned)(slash - resolved);
            if (plen >= sizeof(parent)) plen = sizeof(parent) - 1;
            kmemcpy(parent, resolved, plen);
            parent[plen] = '/';
            parent[plen + 1] = 0;
            if (!fs_dir_exists(parent)) parent_ok = 0;
        }
        if (parent_ok) {
            f->rf = ramdisk_create(resolved, 0);
            if (!f->rf) { kfree(f); return 0; }
        }
    }
    if (!f->rf && minifs_is_mounted()) {
        int ino = minifs_resolve_path(resolved);
        if (ino < 0 && kstrchr(resolved, '/')) {
            const char *base = resolved;
            const char *p;
            for (p = resolved; *p; p++)
                if (*p == '/') base = p + 1;
            ino = minifs_resolve_path(base);
        }
        if (want_write && ino < 0) {
            if (minifs_mkdir_p(resolved) == 0)
                ino = minifs_create(resolved, 0644);
        }
        if (ino >= 0) {
            MiniFSInode st;
            if (minifs_stat(ino, &st) >= 0) {
                f->minifs_ino = ino;
                f->minifs_size = st.size;
                if (want_write && mode[0] == 'w' && st.size > 0)
                    minifs_truncate(ino, 0);
            }
        }
    }
    if (!f->rf && f->minifs_ino < 0) { kfree(f); return 0; }
    f->mode = (mode[0] == 'w') ? 1 : ((mode[0] == 'a') ? 2 : 0);
    f->pos = 0;
    if (f->mode == 2) {
        if (f->rf) f->pos = f->rf->size;
        else if (f->minifs_ino >= 0) f->pos = f->minifs_size;
    }
    if (f->mode != 0 && (f->rf || f->minifs_ino >= 0)) {
        if (f->mode == 1 && f->rf && f->rf->size && !ramdisk_resize(f->rf, 0)) { kfree(f); return 0; }
        f->wbuf = kmalloc(4096);
        f->wcap = 4096;
        f->wsize = 0;
        if (!f->wbuf) { kfree(f); return 0; }
    }
    return f;
}

int kfclose(KFILE *f) {
    int rc = 0;
    if (!f) return 0;
    if (f->mode != 0) {
        rc = kfflush(f);
        if (rc == 0 && f->minifs_ino >= 0 && minifs_is_mounted())
            minifs_sync();
    }
    if (f->wbuf) kfree(f->wbuf);
    kfree(f);
    return rc;
}

int kfgetc(KFILE *f) {
    if (!f) return EOF;
    if (f->is_console) {
        int c = console_getc();
        if (c == '\r') c = '\n';
        return c;
    }
    if (f->minifs_ino >= 0) {
        if (f->pos >= f->minifs_size) return EOF;
        char c;
        minifs_read(f->minifs_ino, &c, f->pos, 1);
        f->pos++;
        return (unsigned char)c;
    }
    if (!f->rf || f->pos >= f->rf->size) return EOF;
    char c;
    ramdisk_read(f->rf, &c, f->pos, 1);
    f->pos++;
    return (unsigned char)c;
}

char *kfgets(char *buf, int size, KFILE *f) {
    int i = 0;
    if (!buf || size <= 0 || !f) return 0;
    while (i < size - 1) {
        int c = kfgetc(f);
        if (c == EOF) break;
        buf[i++] = (char)c;
        if (c == '\n') break;
    }
    if (i == 0) return 0;
    buf[i] = 0;
    return buf;
}

int kfungetc(int c, KFILE *f) {
    if (!f || c == EOF || f->pos == 0) return EOF;
    f->pos--;
    return c;
}

unsigned long kfread(void *ptr, unsigned long size, unsigned long n, KFILE *f) {
    if (!f || !size || !n) return 0;
    if (n > 0 && size > 0xFFFFFFFFUL / n) return 0;
    unsigned long total = size * n;
    if (f->is_console) {
        char *b = ptr; unsigned long got = 0;
        while (got < total) { int c = kfgetc(f); if (c == EOF) break; b[got++] = (char)c; }
        return got / size;
    }
    if (f->minifs_ino >= 0) {
        if (f->pos + total > f->minifs_size) total = f->minifs_size - f->pos;
        minifs_read(f->minifs_ino, ptr, f->pos, (unsigned)total);
        f->pos += total;
        return total / size;
    }
    if (!f->rf) return 0;
    if (f->pos + total > f->rf->size) total = f->rf->size - f->pos;
    ramdisk_read(f->rf, ptr, f->pos, (unsigned)total);
    f->pos += total;
    return total / size;
}

unsigned long kfwrite(const void *ptr, unsigned long size, unsigned long n, KFILE *f) {
    if (!f || !size || !n) return 0;
    if (n > 0 && size > 0xFFFFFFFFUL / n) return 0;
    unsigned long bytes = size * n;
    if (f->is_console) {
        const char *b = ptr; unsigned long i;
        for (i = 0; i < bytes; i++) vga_putc(b[i]);
        return n;
    }
    if (f->mode != 1 && f->mode != 2) return 0;
    if (bytes > RD_DATA_MAX || f->wsize > RD_DATA_MAX - bytes) return 0;
    if (!f->wbuf) {
        f->wbuf = kmalloc(4096);
        f->wcap = 4096;
        f->wsize = 0;
        if (!f->wbuf) return 0;
    }
    while (f->wsize + bytes > f->wcap) {
        if (f->wcap > RD_DATA_MAX / 2) return 0;
        f->wcap *= 2;
        f->wbuf = krealloc(f->wbuf, f->wcap);
        if (!f->wbuf) return 0;
    }
    kmemcpy(f->wbuf + f->wsize, ptr, bytes);
    f->wsize += bytes;
    f->pos += bytes;
    return n;
}

int kfseek(KFILE *f, long offset, int whence) {
    if (!f) return -1;
    unsigned filesize = f->minifs_ino >= 0 ? f->minifs_size : (f->rf ? f->rf->size : 0);
    unsigned base;
    if (whence == 0) base = 0;
    else if (whence == 1) base = f->pos;
    else base = filesize;
    long newp = (long)base + offset;
    if (newp < 0) newp = 0;
    if ((unsigned long)newp > filesize) newp = (long)filesize;
    f->pos = (unsigned)newp;
    return 0;
}

long kftell(KFILE *f) {
    return f ? (long)f->pos : -1;
}

int kfflush(KFILE *f) {
    if (!f || f->mode == 0) return 0;
    if (f->minifs_ino >= 0) {
        if (f->wbuf && f->wsize > 0) {
            unsigned base = (f->mode == 2) ? (unsigned)(f->pos - f->wsize) : 0;
            if (minifs_write(f->minifs_ino, f->wbuf, base, f->wsize) < 0)
                return -1;
            if (base + f->wsize > f->minifs_size)
                f->minifs_size = base + f->wsize;
            f->wsize = 0;
        }
        return 0;
    }
    if (!f->rf) return 0;
    if (f->wbuf && f->wsize > 0) {
        unsigned base = (f->mode == 2) ? (unsigned)(f->pos - f->wsize) : 0;
        if (!ramdisk_resize(f->rf, base + f->wsize)) return -1;
        ramdisk_write(f->rf, f->wbuf, base, f->wsize);
        f->wsize = 0;
    }
    return 0;
}

int kfputs(const char *s, KFILE *f) {
    if (!f || !s) return 0;
    unsigned long len = kstrlen(s);
    return (int)kfwrite(s, 1, len, f);
}

int kfputc(int c, KFILE *f) {
    unsigned char ch = (unsigned char)c;
    return (int)kfwrite(&ch, 1, 1, f);
}

void krewind(KFILE *f) { if (f) kfseek(f, 0, 0); }
