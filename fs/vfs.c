#include "kernel.h"
#include "minifs.h"

/* ================================================================
 *  VFS (Virtual File System) abstraction layer
 * ================================================================ */

#define VFS_MAX_MOUNTS 8
#define VFS_PREFIX_LEN 32

typedef struct {
    char prefix[VFS_PREFIX_LEN];
    const vfs_ops_t *ops;
    int in_use;
} vfs_mount_t;

static vfs_mount_t vfs_mounts[VFS_MAX_MOUNTS];
static int vfs_mount_count;

void vfs_init(void) {
    vfs_mount_count = 0;
    kmemset(vfs_mounts, 0, sizeof(vfs_mounts));
}

int vfs_register(const char *prefix, const vfs_ops_t *ops) {
    if (!prefix || !ops) return -1;
    if (vfs_mount_count >= VFS_MAX_MOUNTS) return -1;
    for (int i = 0; i < VFS_MAX_MOUNTS; i++) {
        if (!vfs_mounts[i].in_use) {
            kstrncpy(vfs_mounts[i].prefix, prefix, VFS_PREFIX_LEN - 1);
            vfs_mounts[i].prefix[VFS_PREFIX_LEN - 1] = 0;
            vfs_mounts[i].ops = ops;
            vfs_mounts[i].in_use = 1;
            vfs_mount_count++;
            return 0;
        }
    }
    return -1;
}

int vfs_unregister(const char *prefix) {
    if (!prefix) return -1;
    for (int i = 0; i < VFS_MAX_MOUNTS; i++) {
        if (vfs_mounts[i].in_use && kstrcmp(vfs_mounts[i].prefix, prefix) == 0) {
            vfs_mounts[i].in_use = 0;
            vfs_mount_count--;
            return 0;
        }
    }
    return -1;
}

int vfs_open(const char *path, int mode, vfs_file_t *f) {
    if (!path || !f) return -1;
    for (int i = 0; i < VFS_MAX_MOUNTS; i++) {
        if (!vfs_mounts[i].in_use) continue;
        unsigned plen = kstrlen(vfs_mounts[i].prefix);
        if (kstrncmp(path, vfs_mounts[i].prefix, plen) == 0 &&
            (path[plen] == '/' || path[plen] == 0 || plen == 0)) {
            const char *subpath = path + plen;
            if (*subpath == '/') subpath++;
            void *handle = 0;
            if (vfs_mounts[i].ops->open) {
                if (vfs_mounts[i].ops->open(subpath, mode, &handle) < 0)
                    return -1;
            }
            f->ops = vfs_mounts[i].ops;
            f->handle = handle;
            f->pos = 0;
            f->mode = mode;
            f->is_console = 0;
            return 0;
        }
    }
    return -1;
}

/* ================================================================
 *  Ramdisk VFS driver
 * ================================================================ */

typedef struct {
    RDFile *rf;
} ramdisk_handle_t;

static int ramdisk_vfs_open(const char *path, int mode, void **handle) {
    RDFile *rf = ramdisk_open(path);
    if (!rf && (mode == 1 || mode == 2)) {
        const char *slash = path + kstrlen(path);
        while (slash > path && slash[-1] != '/') slash--;
        int parent_ok = 1;
        if (slash != path && slash[-1] == '/') {
            char parent[RAMDISK_FNAME_LEN];
            unsigned plen = (unsigned)(slash - path);
            if (plen >= sizeof(parent)) plen = sizeof(parent) - 1;
            kmemcpy(parent, path, plen);
            parent[plen] = '/';
            parent[plen + 1] = 0;
            if (!fs_dir_exists(parent)) parent_ok = 0;
        }
        if (parent_ok) rf = ramdisk_create(path, 0);
    }
    if (!rf) return -1;
    ramdisk_handle_t *h = kmalloc(sizeof(ramdisk_handle_t));
    if (!h) return -1;
    h->rf = rf;
    *handle = h;
    return 0;
}

static int ramdisk_vfs_read(void *handle, void *buf, unsigned long pos, unsigned long len) {
    ramdisk_handle_t *h = (ramdisk_handle_t *)handle;
    if (!h || !h->rf) return -1;
    if (pos + len > h->rf->size) len = h->rf->size - pos;
    if (len == 0) return 0;
    ramdisk_read(h->rf, buf, (unsigned)pos, (unsigned)len);
    return (int)len;
}

static int ramdisk_vfs_write(void *handle, const void *buf, unsigned long pos, unsigned long len) {
    ramdisk_handle_t *h = (ramdisk_handle_t *)handle;
    if (!h || !h->rf) return -1;
    if (!ramdisk_resize(h->rf, (unsigned)(pos + len))) return -1;
    ramdisk_write(h->rf, buf, (unsigned)pos, (unsigned)len);
    return (int)len;
}

static int ramdisk_vfs_close(void *handle) {
    ramdisk_handle_t *h = (ramdisk_handle_t *)handle;
    if (h) kfree(h);
    return 0;
}

static int ramdisk_vfs_fstat(void *handle, unsigned long *size_out) {
    ramdisk_handle_t *h = (ramdisk_handle_t *)handle;
    if (!h || !h->rf || !size_out) return -1;
    *size_out = h->rf->size;
    return 0;
}

static int ramdisk_vfs_truncate(void *handle, unsigned long size) {
    ramdisk_handle_t *h = (ramdisk_handle_t *)handle;
    if (!h || !h->rf) return -1;
    return ramdisk_resize(h->rf, (unsigned)size) ? 0 : -1;
}

static const vfs_ops_t ramdisk_vfs_ops = {
    .open    = ramdisk_vfs_open,
    .read    = ramdisk_vfs_read,
    .write   = ramdisk_vfs_write,
    .close   = ramdisk_vfs_close,
    .fstat   = ramdisk_vfs_fstat,
    .truncate = ramdisk_vfs_truncate,
};

/* ================================================================
 *  MiniFS VFS driver
 * ================================================================ */

typedef struct {
    int ino;
    unsigned size;
} minifs_handle_t;

static int minifs_vfs_open(const char *path, int mode, void **handle) {
    if (!minifs_is_mounted()) return -1;
    int want_write = (mode == 1 || mode == 2);
    int ino = minifs_resolve_path(path);
    if (ino < 0 && kstrchr(path, '/')) {
        const char *base = path;
        const char *p;
        for (p = path; *p; p++)
            if (*p == '/') base = p + 1;
        ino = minifs_resolve_path(base);
    }
    if (want_write && ino < 0) {
        if (minifs_mkdir_p(path) == 0)
            ino = minifs_create(path, 0644);
    }
    if (ino < 0) return -1;
    MiniFSInode st;
    if (minifs_stat(ino, &st) < 0) return -1;
    if (want_write && mode == 1 && st.size > 0)
        minifs_truncate(ino, 0);
    minifs_handle_t *h = kmalloc(sizeof(minifs_handle_t));
    if (!h) return -1;
    h->ino = ino;
    h->size = st.size;
    *handle = h;
    return 0;
}

static int minifs_vfs_read(void *handle, void *buf, unsigned long pos, unsigned long len) {
    minifs_handle_t *h = (minifs_handle_t *)handle;
    if (!h) return -1;
    if (pos + len > h->size) len = h->size - pos;
    if (len == 0) return 0;
    minifs_read(h->ino, buf, pos, (unsigned)len);
    return (int)len;
}

static int minifs_vfs_write(void *handle, const void *buf, unsigned long pos, unsigned long len) {
    minifs_handle_t *h = (minifs_handle_t *)handle;
    if (!h) return -1;
    if (minifs_write(h->ino, buf, (unsigned)pos, (unsigned)len) < 0) return -1;
    if (pos + len > h->size) h->size = (unsigned)(pos + len);
    return (int)len;
}

static int minifs_vfs_close(void *handle) {
    minifs_handle_t *h = (minifs_handle_t *)handle;
    if (h) kfree(h);
    return 0;
}

static int minifs_vfs_fstat(void *handle, unsigned long *size_out) {
    minifs_handle_t *h = (minifs_handle_t *)handle;
    if (!h || !size_out) return -1;
    *size_out = h->size;
    return 0;
}

static int minifs_vfs_truncate(void *handle, unsigned long size) {
    minifs_handle_t *h = (minifs_handle_t *)handle;
    if (!h) return -1;
    return minifs_truncate(h->ino, size);
}

static const vfs_ops_t minifs_vfs_ops = {
    .open    = minifs_vfs_open,
    .read    = minifs_vfs_read,
    .write   = minifs_vfs_write,
    .close   = minifs_vfs_close,
    .fstat   = minifs_vfs_fstat,
    .truncate = minifs_vfs_truncate,
};

/* ================================================================
 *  Path resolution and directory queries
 * ================================================================ */

char fs_cwd[RAMDISK_FNAME_LEN];

int fs_resolve(const char *path, char *out, unsigned cap) {
    unsigned len = 0;
    const char *p = path;
    out[0] = 0;
    if (*p == '/') p++;
    else {
        kmemcpy(out, fs_cwd, kstrlen(fs_cwd) + 1);
        len = (unsigned)kstrlen(out);
    }
    while (*p) {
        const char *start = p;
        while (*p && *p != '/') p++;
        unsigned clen = (unsigned)(p - start);
        if (clen == 0 || (clen == 1 && start[0] == '.')) { if (*p) p++; continue; }
        if (clen == 2 && start[0] == '.' && start[1] == '.') {
            if (len > 0) {
                len--;
                while (len > 0 && out[len - 1] != '/') len--;
                out[len] = 0;
            }
            if (*p) p++;
            continue;
        }
        if (len + 1 + clen >= cap) return 0;
        if (len > 0 && out[len - 1] != '/') out[len++] = '/';
        kmemcpy(out + len, start, clen);
        len += clen;
        out[len] = 0;
        if (*p) p++;
    }
    return 1;
}

int fs_dir_exists(const char *dir) {
    int i, n;
    if (!dir[0]) return 1;
    n = ramdisk_count();
    for (i = 0; i < n; i++)
        if (kstrncmp(ramdisk_file_name(i), dir, kstrlen(dir)) == 0) return 1;
    if (minifs_is_mounted()) {
        unsigned dl = (unsigned)kstrlen(dir);
        if (dl > 0 && dl < RAMDISK_FNAME_LEN) {
            char bare[RAMDISK_FNAME_LEN];
            kmemcpy(bare, dir, dl);
            if (bare[dl - 1] == '/') dl--;
            bare[dl] = 0;
            int ino = minifs_resolve_path(bare);
            if (ino >= 0) {
                MiniFSInode st;
                if (minifs_stat(ino, &st) == 0 &&
                    (st.mode & MINIFS_S_IFDIR) == MINIFS_S_IFDIR)
                    return 1;
            }
        }
    }
    return 0;
}

int fs_is_dir(const char *resolved) {
    unsigned len = (unsigned)kstrlen(resolved);
    if (len == 0) return 0;
    if (resolved[len - 1] == '/') return 1;
    if (ramdisk_open(resolved)) return 0;
    char with_slash[RAMDISK_FNAME_LEN];
    if (len + 1 >= sizeof(with_slash)) return 0;
    kmemcpy(with_slash, resolved, len);
    with_slash[len] = '/';
    with_slash[len + 1] = 0;
    return fs_dir_exists(with_slash);
}

int minifs_mkdir_p(const char *resolved) {
    char dir[RAMDISK_FNAME_LEN];
    unsigned len = 0;
    const char *p = resolved;
    while (*p) {
        const char *start = p;
        while (*p && *p != '/') p++;
        if (*p == 0) break;
        if (p == start) { p++; continue; }
        unsigned clen = (unsigned)(p - start);
        if (len > 0) dir[len++] = '/';
        if (len + clen + 1 >= sizeof(dir)) return -1;
        kmemcpy(dir + len, start, clen);
        len += clen;
        dir[len] = 0;
        if (minifs_resolve_path(dir) < 0) {
            if (minifs_mkdir(dir, 0755) < 0) return -1;
        }
        p++;
    }
    return 0;
}

void vfs_register_builtins(void) {
    vfs_init();
    vfs_register("", &ramdisk_vfs_ops);
    vfs_register("minifs:", &minifs_vfs_ops);
}
