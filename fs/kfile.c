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

/* A KFILE field is a kernel pointer, so it always lives in the canonical
 * low half. A value outside it is the signature of heap corruption (a
 * wild write landed on a live or freed KFILE) or a freed-and-reused slot
 * still referenced by a stale fd. Dereferencing it faults with a #GP and
 * halts the machine with no recovery (the DOOM ABI-drift black screen),
 * so every public KFILE entry point refuses it loudly instead. */
static int kfile_bad_ptr(const void *p) {
    return p && (unsigned long)p >= 0x0000800000000000UL;
}
static int kfile_corrupt(const KFILE *f) {
    return kfile_bad_ptr((const void *)f->rf) || kfile_bad_ptr((const void *)f->vfs) ||
        (f->is_pipe && (kfile_bad_ptr((const void *)f->pring) ||
                         kfile_bad_ptr((const void *)f->pring_ref)));
}

/* A write lands on the ramdisk only when the parent directory entry
 * lives THERE (some ramdisk name carries that prefix). fs_dir_exists is
 * true when the directory lives on either filesystem, which misroutes
 * the second and later files under a MiniFS-only directory (e.g.
 * saves/): the first file falls through to MiniFS and creates the
 * directory there, and every later file then sees "parent exists" and
 * is captured by the volatile ramdisk, vanishing on reboot. */
static int ramdisk_dir_exists(const char *dir) {
    int i, n = ramdisk_count();
    unsigned long dl = kstrlen(dir);
    for (i = 0; i < n; i++)
        if (kstrncmp(ramdisk_file_name(i), dir, dl) == 0) return 1;
    return 0;
}

/* Big filesystem lock: every kf* body below (except the console
 * paths, which block in the console reader and must never hold a
 * spinlock) runs atomically against every other file user, ring-3 or
 * ring-0. MiniFS keeps all of its mutable state (bitmaps, inode
 * table, journal, directory blocks) in unlocked statics, so two
 * processes doing file IO at once tore each other's metadata: wrong
 * block lists, wrong sizes, wrong bytes. The lock is a leaf (never
 * nested, never held across yields) and only ever spans one call, so
 * ticks coalesce instead of deadlocking; heavy IO may delay a tick,
 * which is the documented cost of correctness here. */
spinlock_t fs_lock = SPINLOCK_INIT;

static inline void fs_take(irqflags_t *flags) {
    spin_lock_irqsave(&fs_lock, flags);
}

static inline void fs_drop(irqflags_t flags) {
    spin_unlock_irqrestore(&fs_lock, flags);
}

/** Docstring: Create a connected pipe pair sharing one ring. The read
 * end drains, the write end appends; the ring (and its refcount) dies
 * with the last closed end. Fail-closed: any allocation failure frees
 * what was taken and returns -1 with both outs zeroed. */
int kpipe_pair(KFILE **rend_out, KFILE **wend_out) {
    KFILE *r = 0, *w = 0;
    pipe_ring_t *ring = 0;
    unsigned char *buf = 0;
    int *ref = 0;
    if (!rend_out || !wend_out) return -1;
    *rend_out = 0;
    *wend_out = 0;
    buf = kmalloc(PIPE_CAP_DEFAULT);
    ring = (pipe_ring_t *)kmalloc(sizeof(pipe_ring_t));
    ref = (int *)kmalloc(sizeof(int));
    r = kmalloc(sizeof(KFILE));
    w = kmalloc(sizeof(KFILE));
    if (!buf || !ring || !ref || !r || !w) {
        if (buf) kfree(buf);
        if (ring) kfree(ring);
        if (ref) kfree(ref);
        if (r) kfree(r);
        if (w) kfree(w);
        return -1;
    }
    if (pipe_ring_init(ring, buf, PIPE_CAP_DEFAULT) != 0) {
        kfree(buf); kfree(ring); kfree(ref); kfree(r); kfree(w);
        return -1;
    }
    *ref = 2;
    kmemset(r, 0, sizeof(KFILE));
    kmemset(w, 0, sizeof(KFILE));
    r->is_pipe = 1; r->pipe_write = 0; r->pring = ring; r->pring_ref = ref; r->ref = 1;
    w->is_pipe = 1; w->pipe_write = 1; w->pring = ring; w->pring_ref = ref; w->ref = 1;
    r->minifs_ino = -1;
    w->minifs_ino = -1;
    *rend_out = r;
    *wend_out = w;
    return 0;
}

/** Docstring: True when a pipe read end is empty with the writer still
 * open (retry later, EAGAIN-style), false on EOF, on the write end, or
 * on any non-pipe file. Lets the syscall layer tell "empty" from EOF,
 * which kfread alone reports as 0 items in both cases. */
int kpipe_empty_wopen(KFILE *f) {
    irqflags_t flags;
    int r = 0;
    if (!f || !f->is_pipe || f->pipe_write || !f->pring) return 0;
    fs_take(&flags);
    r = (f->pring->count == 0u && f->pring->wopen) ? 1 : 0;
    fs_drop(flags);
    return r;
}

/** Docstring: True when f is the write end of a pipe. */
int kpipe_is_write_end(KFILE *f) {
    return f && f->is_pipe && f->pipe_write;
}

/** Docstring: Grow a pipe ring buffer, linearizing wrapped bytes first.
 * Returns 0 on success, -1 past PIPE_CAP_MAX or on OOM. The ring keeps
 * its readable bytes in order; only the capacity changes. */
static int kpipe_grow(pipe_ring_t *ring) {
    unsigned newcap;
    unsigned char *nbuf;
    unsigned i;
    if (!ring || !ring->buf) return -1;
    if (ring->cap >= PIPE_CAP_MAX) return -1;
    newcap = ring->cap * 2u;
    if (newcap > PIPE_CAP_MAX) newcap = PIPE_CAP_MAX;
    nbuf = kmalloc(newcap);
    if (!nbuf) return -1;
    for (i = 0u; i < ring->count; i++) {
        nbuf[i] = ring->buf[ring->head];
        ring->head++;
        if (ring->head >= ring->cap) ring->head = 0u;
    }
    kfree(ring->buf);
    ring->buf = nbuf;
    ring->cap = newcap;
    ring->head = 0u;
    ring->tail = ring->count;
    return 0;
}

KFILE *kfopen(const char *path, const char *mode) {
    char resolved[RAMDISK_FNAME_LEN];
    int want_write;
    irqflags_t flags;
    KFILE *f = 0;
    if (!fs_resolve(path, resolved, sizeof(resolved))) return 0;
    if (fs_is_dir(resolved)) return 0;
    f = kmalloc(sizeof(KFILE));
    if (!f) return 0;
    kmemset(f, 0, sizeof(KFILE));
    f->minifs_ino = -1;
    want_write = (mode[0] == 'w' || mode[0] == 'a');

    fs_take(&flags);
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
            /* plen already includes the trailing '/', so NUL-terminate
             * here: appending another '/' ("src//") would never match a
             * ramdisk prefix and silently reroute every pathed write. */
            parent[plen] = 0;
            if (!ramdisk_dir_exists(parent)) parent_ok = 0;
        }
        if (parent_ok) {
            f->rf = ramdisk_create(resolved, 0);
            if (!f->rf) { kfree(f); fs_drop(flags); return 0; }
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
    if (!f->rf && f->minifs_ino < 0) { kfree(f); fs_drop(flags); return 0; }
    f->mode = (mode[0] == 'w') ? 1 : ((mode[0] == 'a') ? 2 : 0);
    f->pos = 0;
    if (f->mode == 2) {
        if (f->rf) f->pos = f->rf->size;
        else if (f->minifs_ino >= 0) f->pos = f->minifs_size;
    }
    if (f->mode != 0 && (f->rf || f->minifs_ino >= 0)) {
        if (f->mode == 1 && f->rf && f->rf->size && !ramdisk_resize(f->rf, 0)) { kfree(f); fs_drop(flags); return 0; }
        f->wbuf = kmalloc(4096);
        f->wcap = 4096;
        f->wsize = 0;
        if (!f->wbuf) { kfree(f); fs_drop(flags); return 0; }
    }
    f->ref = 1;
    fs_drop(flags);
    return f;
}

int kfclose(KFILE *f) {
    int rc = 0;
    irqflags_t flags;
    if (!f) return 0;
    if (f->is_console) {
        if (f->wbuf) kfree(f->wbuf);
        kfree(f);
        return 0;
    }
    if (f->is_pipe) {
        int drop = 0;
        fs_take(&flags);
        if (f->pipe_write && f->pring) pipe_ring_close_writer(f->pring);
        if (f->pring_ref) {
            (*f->pring_ref)--;
            if (*f->pring_ref <= 0) drop = 1;
        } else drop = 1;
        if (drop) {
            if (f->pring) {
                if (f->pring->buf) kfree(f->pring->buf);
                kfree(f->pring);
            }
            if (f->pring_ref) kfree(f->pring_ref);
        }
        fs_drop(flags);
        kfree(f);
        return 0;
    }
    fs_take(&flags);
    if (f->mode != 0) {
        rc = kfflush(f);
        if (rc == 0 && f->minifs_ino >= 0 && minifs_is_mounted())
            minifs_sync();
    }
    if (f->wbuf) kfree(f->wbuf);
    kfree(f);
    fs_drop(flags);
    return rc;
}

int kfgetc(KFILE *f) {
    if (!f) return EOF;
    if (f->is_console) {
        int c = console_getc();
        if (c == '\r') c = '\n';
        return c;
    }
    if (f->is_pipe) {
        irqflags_t flags;
        unsigned char c;
        int n;
        if (!f->pring || kfile_corrupt(f)) return EOF;
        if (f->pipe_write) return EOF;
        fs_take(&flags);
        n = pipe_ring_read(f->pring, &c, 1u);
        fs_drop(flags);
        if (n == PIPE_EMPTY) return EOF;
        if (n <= 0) return EOF;
        return c;
    }
    if (f->minifs_ino >= 0) {
        irqflags_t flags;
        char c;
        int rc;
        fs_take(&flags);
        if (f->pos >= f->minifs_size) rc = EOF;
        else {
            minifs_read(f->minifs_ino, &c, f->pos, 1);
            f->pos++;
            rc = (unsigned char)c;
        }
        fs_drop(flags);
        return rc;
    }
    if (!f->rf || kfile_corrupt(f) || f->pos >= f->rf->size) return EOF;
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
    if (f->is_pipe) return EOF;
    f->pos--;
    return c;
}

unsigned long kfread(void *ptr, unsigned long size, unsigned long n, KFILE *f) {
    unsigned long total;
    unsigned long rc;
    irqflags_t flags;
    if (!f || !size || !n) return 0;
    if (n > 0 && size > 0xFFFFFFFFUL / n) return 0;
    total = size * n;
    if (f->is_console) {
        char *b = ptr; unsigned long got = 0;
        while (got < total) { int c = kfgetc(f); if (c == EOF) break; b[got++] = (char)c; }
        return got / size;
    }
    if (f->is_pipe) {
        /* Read end drains, write end reads nothing. Empty with the
         * writer open is EAGAIN-style (0 items, not EOF): the caller
         * yields and retries. Empty with the writer closed is EOF. */
        char *b = ptr;
        int n;
        if (!f->pring || kfile_corrupt(f)) return 0;
        if (f->pipe_write) return 0;
        fs_take(&flags);
        n = pipe_ring_read(f->pring, (unsigned char *)b, (unsigned)total);
        fs_drop(flags);
        if (n == PIPE_EMPTY) return 0;
        if (n <= 0) return 0;
        return (unsigned long)n / size;
    }
    fs_take(&flags);
    if (f->minifs_ino >= 0) {
        if (f->pos + total > f->minifs_size) total = f->minifs_size - f->pos;
        minifs_read(f->minifs_ino, ptr, f->pos, (unsigned)total);
        f->pos += total;
        rc = total / size;
    } else if (!f->rf || kfile_corrupt(f)) {
        rc = 0;
    } else {
        if (f->pos + total > f->rf->size) total = f->rf->size - f->pos;
        ramdisk_read(f->rf, ptr, f->pos, (unsigned)total);
        f->pos += total;
        rc = total / size;
    }
    fs_drop(flags);
    return rc;
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
    if (f->is_pipe) {
        /* Write end appends (growing to PIPE_CAP_MAX, partial past
         * it); read end writes nothing. Never blocks: a full ring
         * past the cap reports what fit, never a silent drop. */
        const unsigned char *b = ptr;
        unsigned wrote = 0u;
        if (!f->pring || kfile_corrupt(f)) return 0;
        if (!f->pipe_write) return 0;
        {
            irqflags_t flags;
            fs_take(&flags);
            while (wrote < bytes) {
                unsigned n = pipe_ring_write(f->pring, b + wrote,
                                             (unsigned)(bytes - wrote));
                wrote += n;
                if (wrote >= bytes) break;
                if (kpipe_grow(f->pring) != 0) break;
            }
            fs_drop(flags);
        }
        return wrote / size;
    }
    if (f->mode != 1 && f->mode != 2) return 0;
    if (bytes > RD_DATA_MAX || f->wsize > RD_DATA_MAX - bytes) return 0;
    {
        irqflags_t flags;
        fs_take(&flags);
        if (!f->wbuf) {
            f->wbuf = kmalloc(4096);
            f->wcap = 4096;
            f->wsize = 0;
            if (!f->wbuf) { fs_drop(flags); return 0; }
        }
        while (f->wsize + bytes > f->wcap) {
            if (f->wcap > RD_DATA_MAX / 2) { fs_drop(flags); return 0; }
            f->wcap *= 2;
            f->wbuf = krealloc(f->wbuf, f->wcap);
            if (!f->wbuf) { fs_drop(flags); return 0; }
        }
        kmemcpy(f->wbuf + f->wsize, ptr, bytes);
        f->wsize += bytes;
        f->pos += bytes;
        fs_drop(flags);
    }
    return n;
}

int kfseek(KFILE *f, long offset, int whence) {
    if (!f) return -1;
    if (f->is_pipe) return -1;
    if (kfile_corrupt(f)) {
        kprintf("kfile: corrupt handle (rf=%lx vfs=%lx) on seek - refusing\n",
                (unsigned long)f->rf, (unsigned long)f->vfs);
        return -1;
    }
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
    if (!f->rf || kfile_corrupt(f)) return 0;
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
