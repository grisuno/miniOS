#include "kernel.h"
#include "minifs.h"
#include "fat32.h"
#include "ext4.h"

/* ================================================================
 *  VFS (Virtual File System) abstraction layer
 * ================================================================ */

typedef struct {
    char prefix[VFS_PREFIX_LEN];
    char driver[VFS_DRIVER_LEN];
    const vfs_ops_t *ops;
    int in_use;
    int open_refs;
} vfs_mount_t;

static vfs_mount_t vfs_mounts[VFS_MAX_MOUNTS];
static int vfs_mount_count;
static spinlock_t vfs_lock = SPINLOCK_INIT;

void vfs_init(void) {
    vfs_mount_count = 0;
    kmemset(vfs_mounts, 0, sizeof(vfs_mounts));
}

int vfs_register(const char *prefix, const vfs_ops_t *ops, const char *driver) {
    irqflags_t flags;
    int rc = -1, i;
    if (!prefix || !ops) return -1;
    if (kstrlen(prefix) >= VFS_PREFIX_LEN) return -1;
    spin_lock_irqsave(&vfs_lock, &flags);
    if (vfs_mount_count >= VFS_MAX_MOUNTS) { spin_unlock_irqrestore(&vfs_lock, flags); return -1; }
    for (i = 0; i < VFS_MAX_MOUNTS; i++) {
        if (vfs_mounts[i].in_use && kstrcmp(vfs_mounts[i].prefix, prefix) == 0) {
            spin_unlock_irqrestore(&vfs_lock, flags);
            return -1;
        }
    }
    for (i = 0; i < VFS_MAX_MOUNTS; i++) {
        if (!vfs_mounts[i].in_use) {
            kstrncpy(vfs_mounts[i].prefix, prefix, VFS_PREFIX_LEN - 1);
            vfs_mounts[i].prefix[VFS_PREFIX_LEN - 1] = 0;
            if (driver && driver[0]) {
                kstrncpy(vfs_mounts[i].driver, driver, VFS_DRIVER_LEN - 1);
                vfs_mounts[i].driver[VFS_DRIVER_LEN - 1] = 0;
            } else {
                kstrncpy(vfs_mounts[i].driver, "?", VFS_DRIVER_LEN - 1);
            }
            vfs_mounts[i].ops = ops;
            vfs_mounts[i].in_use = 1;
            vfs_mounts[i].open_refs = 0;
            vfs_mount_count++;
            rc = 0;
            break;
        }
    }
    spin_unlock_irqrestore(&vfs_lock, flags);
    return rc;
}

int vfs_unregister(const char *prefix) {
    irqflags_t flags;
    int rc = -1, i;
    if (!prefix) return -1;
    if (!prefix[0]) return -22;
    spin_lock_irqsave(&vfs_lock, &flags);
    for (i = 0; i < VFS_MAX_MOUNTS; i++) {
        if (vfs_mounts[i].in_use && kstrcmp(vfs_mounts[i].prefix, prefix) == 0) {
            if (vfs_mounts[i].open_refs > 0) {
                spin_unlock_irqrestore(&vfs_lock, flags);
                return -16;
            }
            vfs_mounts[i].in_use = 0;
            vfs_mounts[i].ops = 0;
            vfs_mount_count--;
            rc = 0;
            break;
        }
    }
    spin_unlock_irqrestore(&vfs_lock, flags);
    return rc;
}

/** Docstring: Mount table snapshot for the `mount` builtin. Returns the
 * slot count filled (up to cap). Fail-closed on null output. */
int vfs_list(char prefixes[][VFS_PREFIX_LEN], char drivers[][VFS_DRIVER_LEN],
        int refs[], int cap) {
    irqflags_t flags;
    int n = 0, i;
    if (!prefixes || !drivers || !refs || cap <= 0) return 0;
    spin_lock_irqsave(&vfs_lock, &flags);
    for (i = 0; i < VFS_MAX_MOUNTS && n < cap; i++) {
        if (!vfs_mounts[i].in_use) continue;
        kstrncpy(prefixes[n], vfs_mounts[i].prefix, VFS_PREFIX_LEN - 1);
        prefixes[n][VFS_PREFIX_LEN - 1] = 0;
        kstrncpy(drivers[n], vfs_mounts[i].driver, VFS_DRIVER_LEN - 1);
        drivers[n][VFS_DRIVER_LEN - 1] = 0;
        refs[n] = vfs_mounts[i].open_refs;
        n++;
    }
    spin_unlock_irqrestore(&vfs_lock, flags);
    return n;
}

int vfs_open(const char *path, int mode, vfs_file_t *f) {
    irqflags_t flags;
    int best = -1;
    unsigned best_len = 0;
    int i;
    if (!path || !f) return -1;
    if (mode < 0 || mode > 2) return -1;
    /* Longest-prefix-first (the documented contract): the root ""
     * matches everything, so first-match would bury every later
     * mount. The best match wins; ties keep the earliest slot. */
    spin_lock_irqsave(&vfs_lock, &flags);
    for (i = 0; i < VFS_MAX_MOUNTS; i++) {
        unsigned plen;
        if (!vfs_mounts[i].in_use) continue;
        plen = kstrlen(vfs_mounts[i].prefix);
        if (plen < best_len) continue;
        if (kstrncmp(path, vfs_mounts[i].prefix, plen) == 0 &&
            (path[plen] == '/' || path[plen] == 0 || plen == 0)) {
            if (plen > best_len || best < 0) {
                best = i;
                best_len = plen;
            }
        }
    }
    if (best >= 0) vfs_mounts[best].open_refs++;
    spin_unlock_irqrestore(&vfs_lock, flags);
    if (best < 0) return -1;
    {
        const char *subpath = path + best_len;
        void *handle = 0;
        if (*subpath == '/') subpath++;
        if (vfs_mounts[best].ops->open) {
            if (vfs_mounts[best].ops->open(subpath, mode, &handle) < 0) {
                spin_lock_irqsave(&vfs_lock, &flags);
                vfs_mounts[best].open_refs--;
                spin_unlock_irqrestore(&vfs_lock, flags);
                return -1;
            }
        }
        f->ops = vfs_mounts[best].ops;
        f->handle = handle;
        f->pos = 0;
        f->mode = mode;
        f->is_console = 0;
        f->mount_idx = best;
        return 0;
    }
}

/** Docstring: List one directory through the ops table, no caller
 * branch on the backing driver. Stateless like a single getdents:
 * longest-prefix match selects the driver, the subpath strips the
 * prefix exactly like open, and a missing readdir verb refuses
 * instead of falling back to a driver-specific list. No mount
 * refcount is taken (ops tables are static, never freed), so a
 * listing can never pin an unmount the way an open handle does. */
int vfs_readdir(const char *path, vfs_dirent_t *ents, int cap) {
    irqflags_t flags;
    int best = -1;
    unsigned best_len = 0;
    int i;
    const vfs_ops_t *ops;
    const char *subpath;
    if (!path || !ents || cap <= 0) return -1;
    spin_lock_irqsave(&vfs_lock, &flags);
    for (i = 0; i < VFS_MAX_MOUNTS; i++) {
        unsigned plen;
        if (!vfs_mounts[i].in_use) continue;
        plen = kstrlen(vfs_mounts[i].prefix);
        if (plen < best_len) continue;
        if (kstrncmp(path, vfs_mounts[i].prefix, plen) == 0 &&
            (path[plen] == '/' || path[plen] == 0 || plen == 0)) {
            if (plen > best_len || best < 0) {
                best = i;
                best_len = plen;
            }
        }
    }
    ops = best >= 0 ? vfs_mounts[best].ops : 0;
    spin_unlock_irqrestore(&vfs_lock, flags);
    if (!ops || !ops->readdir) return -1;
    subpath = path + best_len;
    if (*subpath == '/') subpath++;
    return ops->readdir(subpath, ents, cap);
}

/* ================================================================
 *  Ramdisk VFS driver
 * ================================================================ */

typedef struct {
    RDFile *rf;
} ramdisk_handle_t;

/* Same contract as kfopen: a write lands on the ramdisk only when the
 * parent directory entry lives there, never merely because fs_dir_exists
 * sees it on MiniFS (that misroute loses every post-first file under a
 * MiniFS-only directory on reboot). */
static int ramdisk_vfs_dir_exists(const char *dir) {
    int i, n = ramdisk_count();
    unsigned long dl = kstrlen(dir);
    for (i = 0; i < n; i++)
        if (kstrncmp(ramdisk_file_name(i), dir, dl) == 0) return 1;
    return 0;
}

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
            /* plen already includes the trailing '/'; appending another
             * one ("src//") would never match a ramdisk prefix. */
            parent[plen] = 0;
            if (!ramdisk_vfs_dir_exists(parent)) parent_ok = 0;
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

/** Docstring: List ramdisk leaves under dir ("" or "/" is root).
 * Flat names with "/" as data split into leaves and first-level
 * subdirectories, deduplicated, so "src/sub/x" contributes "sub"
 * once and "src/" contributes "src" as a directory. */
static int ramdisk_vfs_readdir(const char *path, vfs_dirent_t *ents,
        int cap) {
    unsigned long dl;
    int n = 0;
    int i;
    if (!path || !ents || cap <= 0) return -1;
    while (*path == '/') path++;
    dl = kstrlen(path);
    if (dl >= (unsigned long)RAMDISK_FNAME_LEN) return -1;
    for (i = 0; i < ramdisk_count(); i++) {
        const char *nm = ramdisk_file_name(i);
        const char *rest;
        const char *slash;
        unsigned long leaf;
        int isdir;
        int k;
        int dup = 0;
        if (!nm || !nm[0]) continue;
        if (dl == 0) {
            rest = nm;
        } else {
            if (kstrncmp(nm, path, dl) != 0) continue;
            if (nm[dl] != '/' && nm[dl] != 0) continue;
            if (nm[dl] == 0) continue;
            rest = nm + dl + 1;
        }
        if (!rest[0]) continue;
        slash = kstrchr(rest, '/');
        if (!slash) {
            leaf = kstrlen(rest);
            isdir = 0;
        } else if (!slash[1]) {
            leaf = (unsigned long)(slash - rest);
            isdir = 1;
        } else {
            leaf = (unsigned long)(slash - rest);
            isdir = 1;
        }
        if (leaf == 0 || leaf > (unsigned long)VFS_NAME_MAX) continue;
        for (k = 0; k < n; k++) {
            if (kstrncmp(ents[k].name, rest, leaf) == 0 &&
                    ents[k].name[leaf] == 0 && ents[k].isdir == isdir)
                dup = 1;
        }
        if (dup) continue;
        if (n >= cap) break;
        kmemcpy(ents[n].name, rest, leaf);
        ents[n].name[leaf] = 0;
        ents[n].isdir = isdir;
        n++;
    }
    return n;
}

static const vfs_ops_t ramdisk_vfs_ops = {
    .open    = ramdisk_vfs_open,
    .read    = ramdisk_vfs_read,
    .write   = ramdisk_vfs_write,
    .close   = ramdisk_vfs_close,
    .fstat   = ramdisk_vfs_fstat,
    .truncate = ramdisk_vfs_truncate,
    .readdir = ramdisk_vfs_readdir,
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

/** Docstring: List MiniFS directory entries by index order, faithful
 * to what the directory holds (no dot filtering). Non-directories
 * refuse with -20, missing paths with the resolver's -1. */
static int minifs_vfs_readdir(const char *path, vfs_dirent_t *ents,
        int cap) {
    int ino;
    MiniFSInode st;
    MiniFSDirEntry de;
    char name[RAMDISK_FNAME_LEN];
    int idx = 0;
    int n = 0;
    if (!minifs_is_mounted() || !path || !ents || cap <= 0) return -1;
    while (*path == '/') path++;
    ino = minifs_resolve_path(path);
    if (ino < 0) return -1;
    if (minifs_stat(ino, &st) < 0) return -1;
    if (!(st.mode & MINIFS_S_IFDIR)) return -20;
    while (n < cap) {
        if (minifs_dir_read(ino, idx, &de, name) != 0) break;
        idx++;
        kstrncpy(ents[n].name, name, VFS_NAME_MAX);
        ents[n].name[VFS_NAME_MAX] = 0;
        ents[n].isdir = (de.file_type == MINIFS_FT_DIR);
        n++;
    }
    return n;
}

static const vfs_ops_t minifs_vfs_ops = {
    .open    = minifs_vfs_open,
    .read    = minifs_vfs_read,
    .write   = minifs_vfs_write,
    .close   = minifs_vfs_close,
    .fstat   = minifs_vfs_fstat,
    .truncate = minifs_vfs_truncate,
    .readdir = minifs_vfs_readdir,
};

/* ================================================================
 *  mem: volatile in-memory driver (dynamic-mount proof)
 * ================================================================ */

#define MEM_FILES 8
#define MEM_FNAME 32
#define MEM_FSIZE 1024

typedef struct {
    char name[MEM_FNAME];
    unsigned char data[MEM_FSIZE];
    unsigned size;
    int used;
} mem_file_t;

static mem_file_t mem_files[MEM_FILES];

static int mem_lookup(const char *path) {
    int i;
    for (i = 0; i < MEM_FILES; i++)
        if (mem_files[i].used && kstrcmp(mem_files[i].name, path) == 0)
            return i;
    return -1;
}

static int mem_open(const char *path, int mode, void **handle) {
    int i = mem_lookup(path);
    if (!path || !path[0] || kstrlen(path) >= MEM_FNAME) return -1;
    if (mode < 0 || mode > 2) return -1;
    if (i < 0) {
        if (mode == 0) return -1;
        for (i = 0; i < MEM_FILES; i++)
            if (!mem_files[i].used) break;
        if (i >= MEM_FILES) return -1;
        kstrncpy(mem_files[i].name, path, MEM_FNAME - 1);
        mem_files[i].name[MEM_FNAME - 1] = 0;
        mem_files[i].size = 0;
        mem_files[i].used = 1;
    } else if (mode == 1) {
        mem_files[i].size = 0;
    }
    *handle = (void *)(unsigned long)(i + 1);
    return 0;
}

static int mem_slot(void *handle) {
    unsigned long i = (unsigned long)handle;
    if (i < 1u || i > (unsigned long)MEM_FILES) return -1;
    if (!mem_files[i - 1].used) return -1;
    return (int)(i - 1);
}

static int mem_read(void *handle, void *buf, unsigned long pos, unsigned long len) {
    int i = mem_slot(handle);
    if (i < 0 || !buf) return -1;
    if (pos >= mem_files[i].size) return 0;
    if (pos + len > mem_files[i].size) len = mem_files[i].size - pos;
    if (len == 0) return 0;
    kmemcpy(buf, mem_files[i].data + pos, len);
    return (int)len;
}

static int mem_write(void *handle, const void *buf, unsigned long pos, unsigned long len) {
    int i = mem_slot(handle);
    if (i < 0 || !buf) return -1;
    if (pos >= MEM_FSIZE) return 0;
    if (pos + len > MEM_FSIZE) len = MEM_FSIZE - pos;
    if (len == 0) return 0;
    kmemcpy(mem_files[i].data + pos, buf, len);
    if (pos + len > mem_files[i].size) mem_files[i].size = (unsigned)(pos + len);
    return (int)len;
}

static int mem_close(void *handle) {
    return mem_slot(handle) < 0 ? -1 : 0;
}

static int mem_fstat(void *handle, unsigned long *size_out) {
    int i = mem_slot(handle);
    if (i < 0 || !size_out) return -1;
    *size_out = mem_files[i].size;
    return 0;
}

static int mem_truncate(void *handle, unsigned long size) {
    int i = mem_slot(handle);
    if (i < 0 || size > MEM_FSIZE) return -1;
    if (size > mem_files[i].size)
        kmemset(mem_files[i].data + mem_files[i].size, 0, size - mem_files[i].size);
    mem_files[i].size = (unsigned)size;
    return 0;
}

/** Docstring: List the flat mem: namespace (root only, files only).
 * Anything below root refuses: there are no directories here. */
static int mem_readdir(const char *path, vfs_dirent_t *ents, int cap) {
    int n = 0;
    int i;
    if (!path || !ents || cap <= 0) return -1;
    while (*path == '/') path++;
    if (*path != 0) return -1;
    for (i = 0; i < MEM_FILES && n < cap; i++) {
        if (!mem_files[i].used) continue;
        kstrncpy(ents[n].name, mem_files[i].name, VFS_NAME_MAX);
        ents[n].name[VFS_NAME_MAX] = 0;
        ents[n].isdir = 0;
        n++;
    }
    return n;
}

static const vfs_ops_t mem_vfs_ops = {
    .open    = mem_open,
    .read    = mem_read,
    .write   = mem_write,
    .close   = mem_close,
    .fstat   = mem_fstat,
    .truncate = mem_truncate,
    .readdir = mem_readdir,
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
    vfs_register("", &ramdisk_vfs_ops, "ramdisk");
    vfs_register("minifs:", &minifs_vfs_ops, "minifs");
    vfs_register("mem:", &mem_vfs_ops, "mem");
    vfs_register("fat:", &fat32_vfs_ops, "fat");
    vfs_register("ext4:", &ext4_vfs_ops, "ext4");
}

/** Docstring: Mount a known driver under a prefix (the `mount` builtin
 * path). driver names ramdisk, minifs, mem, fat or ext4; anything
 * else refuses. A duplicate prefix refuses like a duplicate
 * registration, never an alias. The root "" stays pinned: mounting
 * over it refuses. The fat/ext4 drivers parse "imgpath:inpath" per
 * open (loopback image file plus in-image path), so one registration
 * serves every image. */
int vfs_mount_driver(const char *prefix, const char *driver) {
    const vfs_ops_t *ops = 0;
    if (!prefix || !prefix[0] || !driver) return -1;
    if (kstrcmp(driver, "ramdisk") == 0) ops = &ramdisk_vfs_ops;
    else if (kstrcmp(driver, "minifs") == 0) ops = &minifs_vfs_ops;
    else if (kstrcmp(driver, "mem") == 0) ops = &mem_vfs_ops;
    else if (kstrcmp(driver, "fat") == 0) ops = &fat32_vfs_ops;
    else if (kstrcmp(driver, "ext4") == 0) ops = &ext4_vfs_ops;
    else return -1;
    return vfs_register(prefix, ops, driver);
}

/* ================================================================
 *  Facade dispatch: pure ops-table calls, no filesystem branches.
 *  A caller holding a vnode never asks which driver backs it; that is
 *  the Open/Closed guarantee. All paths fail closed (-1) on a null
 *  vnode, a null ops table or a missing operation.
 * ================================================================ */

int vfs_read(vfs_file_t *f, void *buf, unsigned long len) {
    int n;
    if (!f || !f->ops || !f->ops->read || !buf) return -1;
    if (len == 0) return 0;
    n = f->ops->read(f->handle, buf, f->pos, len);
    if (n > 0) f->pos += (unsigned)n;
    return n;
}

int vfs_write(vfs_file_t *f, const void *buf, unsigned long len) {
    int n;
    if (!f || !f->ops || !f->ops->write || !buf) return -1;
    if (len == 0) return 0;
    /* Append mode writes at the end regardless of pos (the ops
     * contract): rebase pos from the live size first, so a reopened
     * append handle (pos 0) cannot overwrite the head. */
    if (f->mode == 2 && f->ops->fstat) {
        unsigned long sz = 0;
        if (f->ops->fstat(f->handle, &sz) == 0) f->pos = (unsigned)sz;
    }
    n = f->ops->write(f->handle, buf, f->pos, len);
    if (n > 0) f->pos += (unsigned)n;
    return n;
}

int vfs_close(vfs_file_t *f) {
    int rc;
    irqflags_t flags;
    if (!f || !f->ops || !f->ops->close) return -1;
    rc = f->ops->close(f->handle);
    if (f->mount_idx >= 0 && f->mount_idx < VFS_MAX_MOUNTS) {
        spin_lock_irqsave(&vfs_lock, &flags);
        if (vfs_mounts[f->mount_idx].in_use &&
                vfs_mounts[f->mount_idx].open_refs > 0)
            vfs_mounts[f->mount_idx].open_refs--;
        spin_unlock_irqrestore(&vfs_lock, flags);
    }
    f->ops = 0;
    f->handle = 0;
    f->mount_idx = -1;
    return rc;
}

int vfs_fstat(vfs_file_t *f, unsigned long *size_out) {
    if (!f || !f->ops || !f->ops->fstat || !size_out) return -1;
    return f->ops->fstat(f->handle, size_out);
}
