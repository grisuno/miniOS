/* zip.c — the unzip/zip shell builtins over the miniz zip library.
 *
 * Both builtins work whole-file in memory over the unified file API,
 * matching the compression tools contract: an archive is validated before
 * any entry is published, output is written only after the whole archive was
 * read, and every failure path reports a diagnostic and releases. Entry
 * names are hostile data: each is normalized to forward slashes and rejected
 * when it escapes the extraction root (absolute paths, '.'/'..' components,
 * empty names), so a crafted archive can never write outside the directory
 * the user named.
 *
 * miniz runs on the kernel heap (see third_party/miniz/miniz_impl.c); this
 * file only calls its public API.
 */
#include "kernel.h"
#include "miniz.h"

void *mz_zip_writer_mem_ptr(mz_zip_archive *pZip);
size_t mz_zip_writer_mem_size(mz_zip_archive *pZip);

/* Read a whole file (ramdisk first, MiniFS fallback) into a fresh kernel
 * buffer, growing until the read stops making progress. The buffer is
 * bounded by the file size, so a hostile file cannot drive an oversized
 * allocation. Returns 0 on failure. */
static unsigned char *zip_read_whole(const char *path, unsigned long *size) {
    KFILE *f = kfopen(path, "r");
    unsigned char *buf = 0;
    unsigned long total = 0;
    if (!f) return 0;
    for (;;) {
        unsigned char *nb;
        unsigned long got;
        if (total + 4096 < total) { kfree(buf); kfclose(f); return 0; }
        nb = krealloc(buf, total + 4096);
        if (!nb) { kfree(buf); kfclose(f); return 0; }
        buf = nb;
        got = kfread(buf + total, 1, 4096, f);
        total += got;
        if (got == 0) break;
    }
    kfclose(f);
    if (total == 0) { kfree(buf); return 0; }
    *size = total;
    return buf;
}

/* Normalize a zip entry name to a safe relative path. Converts backslashes
 * to slashes, strips leading '/' and './' repetitions, and returns 0 when
 * the name is empty or contains an escaping '.'/'..' component. A directory
 * marker (trailing '/') is preserved by the caller, not here. */
static int zip_sanitize_name(const char *src, char *dst, unsigned cap) {
    unsigned len = 0;
    const char *p = src;
    for (;;) {
        if (*p == '/') { p++; continue; }
        if (p[0] == '.' && p[1] == '/') { p += 2; continue; }
        break;
    }
    while (*p) {
        const char *start = p;
        while (*p && *p != '/' && *p != '\\') p++;
        unsigned clen = (unsigned)(p - start);
        if (clen == 1 && start[0] == '.') { if (*p) p++; continue; }
        if (clen == 2 && start[0] == '.' && start[1] == '.') return 0;
        if (clen == 0) { if (*p) p++; continue; }
        if (len + 1 + clen >= cap) return 0;
        if (len > 0 && dst[len - 1] != '/') dst[len++] = '/';
        kmemcpy(dst + len, start, clen);
        len += clen;
        dst[len] = 0;
        if (*p) p++;
    }
    return len > 0;
}

/* Build the combined extraction path: destdir (already resolved, may be "")
 * joined with the sanitized entry name. Returns 1 and fills `out` when the
 * path fits. */
static int zip_build_path(const char *destdir, const char *name, char *out) {
    unsigned dl = destdir ? (unsigned)kstrlen(destdir) : 0;
    unsigned nl = (unsigned)kstrlen(name);
    if (dl + (dl ? 1 : 0) + nl + 1 > RAMDISK_FNAME_LEN) return 0;
    if (dl) {
        kmemcpy(out, destdir, dl);
        out[dl] = '/';
        dl++;
    }
    kmemcpy(out + dl, name, nl + 1);
    return 1;
}

/* Create every directory component of `dir` (a resolved, slash-separated
 * name with no trailing '/'), including `dir` itself, as ramdisk directory
 * markers. Returns 1 on success; the root (empty) always succeeds. */
static int zip_ensure_dir_tree(const char *dir) {
    char m[RAMDISK_FNAME_LEN];
    unsigned len = (unsigned)kstrlen(dir), i;
    if (len == 0) return 1;
    for (i = 0; i <= len; i++) {
        unsigned dl;
        if (i < len && dir[i] != '/') continue;
        if (i == 0) continue;
        dl = i;
        if (dl + 2 >= sizeof(m)) return 0;
        kmemcpy(m, dir, dl);
        m[dl] = '/';
        m[dl + 1] = 0;
        if (!fs_dir_exists(m)) {
            if (!ramdisk_create(m, 0)) return 0;
        }
    }
    return 1;
}

/* Extract one archive entry under destdir. Junk entries (empty or '.'-only
 * names) are skipped and count as success. Returns 1 on success. */
static int zip_do_entry(mz_zip_archive *zip, mz_uint idx, const char *destdir) {
    mz_zip_archive_file_stat st;
    char name[RAMDISK_FNAME_LEN];
    char combined[RAMDISK_FNAME_LEN];
    char resolved[RAMDISK_FNAME_LEN];
    int is_dir;
    if (!mz_zip_reader_file_stat(zip, idx, &st)) return 0;
    is_dir = st.m_is_directory;
    if (!zip_sanitize_name(st.m_filename, name, sizeof(name))) return 1;
    if (is_dir) {
        unsigned nl = (unsigned)kstrlen(name);
        if (nl + 2 >= sizeof(name)) return 0;
        name[nl] = '/';
        name[nl + 1] = 0;
        if (!zip_build_path(destdir, name, combined)) return 0;
        if (!fs_resolve(combined, resolved, sizeof(resolved))) return 0;
        {
            unsigned rl = (unsigned)kstrlen(resolved);
            while (rl > 0 && resolved[rl - 1] == '/') resolved[--rl] = 0;
        }
        if (!zip_ensure_dir_tree(resolved)) return 0;
        return 1;
    }
    if (!zip_build_path(destdir, name, combined)) return 0;
    if (!fs_resolve(combined, resolved, sizeof(resolved))) return 0;
    {
        unsigned rl = (unsigned)kstrlen(resolved);
        unsigned pl;
        if (rl == 0) return 0;
        if (resolved[rl - 1] == '/') return 1; /* file resolved into a dir boundary */
        pl = rl;
        while (pl > 0 && resolved[pl - 1] != '/') pl--;
        if (pl > 0) {
            char parent[RAMDISK_FNAME_LEN];
            kmemcpy(parent, resolved, pl - 1);
            parent[pl - 1] = 0;
            if (!zip_ensure_dir_tree(parent)) return 0;
        }
    }
    {
        unsigned long usize = (unsigned long)st.m_uncomp_size;
        size_t n = 0;
        void *data = mz_zip_reader_extract_to_heap(zip, idx, &n, 0);
        int rc;
        KFILE *f;
        if (!data) return 0;
        if (n != usize) { mz_free(data); return 0; }
        f = kfopen(resolved, "w");
        if (!f) { mz_free(data); return 0; }
        rc = (kfwrite(data, 1, usize, f) == usize) ? 0 : -1;
        if (kfclose(f) != 0) rc = -1;
        mz_free(data);
        if (rc != 0) return 0;
        kprintf("  %-24s %lu bytes\n", resolved, usize);
    }
    return 1;
}

/* unzip <archive.zip> [dir]  — extract;  unzip -l <archive.zip> — list. */
void shell_cmd_unzip(int argc, char **argv) {
    const char *archive;
    char destbuf[RAMDISK_FNAME_LEN];
    const char *destdir = 0;
    int list_only = 0;
    unsigned long asize;
    unsigned char *abuf;
    mz_zip_archive zip;
    mz_uint i, n;
    int fail = 0, extracted = 0;

    if (argc < 2) { vga_puts("usage: unzip <archive.zip> [dir]  (or -l to list)\n"); return; }
    if (kstrcmp(argv[1], "-l") == 0) {
        list_only = 1;
        if (argc < 3) { vga_puts("usage: unzip -l <archive.zip>\n"); return; }
        archive = argv[2];
    } else {
        archive = argv[1];
        if (argc >= 3) {
            unsigned dl;
            if (!fs_resolve(argv[2], destbuf, sizeof(destbuf))) {
                kprintf("unzip: %s: name too long\n", argv[2]);
                return;
            }
            dl = (unsigned)kstrlen(destbuf);
            while (dl > 0 && destbuf[dl - 1] == '/') destbuf[--dl] = 0;
            if (dl == 0) { destdir = 0; }
            else {
                if (ramdisk_open(destbuf)) {
                    kprintf("unzip: %s: not a directory\n", argv[2]);
                    return;
                }
                if (!zip_ensure_dir_tree(destbuf)) {
                    kprintf("unzip: %s: cannot create directory\n", argv[2]);
                    return;
                }
                destdir = destbuf;
            }
        }
    }

    abuf = zip_read_whole(archive, &asize);
    if (!abuf) { kprintf("unzip: %s: cannot read\n", archive); return; }
    kmemset(&zip, 0, sizeof(zip));
    if (!mz_zip_reader_init_mem(&zip, abuf, (size_t)asize, 0)) {
        kprintf("unzip: %s: not a zip archive\n", archive);
        kfree(abuf);
        return;
    }
    n = mz_zip_reader_get_num_files(&zip);
    if (list_only) {
        for (i = 0; i < n; i++) {
            mz_zip_archive_file_stat st;
            if (mz_zip_reader_file_stat(&zip, i, &st))
                kprintf("  %c %lu  %s\n", st.m_is_directory ? 'd' : 'f',
                        (unsigned long)st.m_uncomp_size, st.m_filename);
        }
        kprintf("unzip: %u entries\n", (unsigned)n);
    } else {
        for (i = 0; i < n; i++) {
            if (!zip_do_entry(&zip, i, destdir)) {
                kprintf("unzip: %s: entry %u failed\n", archive, (unsigned)i);
                fail = 1;
                break;
            }
            extracted++;
        }
        if (fail)
            kprintf("unzip: %s: extraction aborted\n", archive);
        else
            kprintf("unzip: %u entries extracted\n", extracted);
    }
    mz_zip_reader_end(&zip);
    kfree(abuf);
}

/* zip <out.zip> <file...> — store each file (under its sanitized name) into
 * a new archive. */
void shell_cmd_zip(int argc, char **argv) {
    mz_zip_archive zip;
    int i, fail = 0;
    unsigned char *obuf;
    unsigned long osize;
    KFILE *f;

    if (argc < 3) { vga_puts("usage: zip <out.zip> <file...>\n"); return; }
    kmemset(&zip, 0, sizeof(zip));
    if (!mz_zip_writer_init_heap(&zip, 0, 0)) {
        vga_puts("zip: cannot initialise archive\n");
        return;
    }
    for (i = 2; i < argc; i++) {
        char name[RAMDISK_FNAME_LEN];
        unsigned long fsize;
        unsigned char *fbuf = zip_read_whole(argv[i], &fsize);
        if (!fbuf) {
            kprintf("zip: %s: cannot read\n", argv[i]);
            fail = 1;
            break;
        }
        if (!zip_sanitize_name(argv[i], name, sizeof(name))) {
            kprintf("zip: %s: invalid archive name\n", argv[i]);
            kfree(fbuf);
            fail = 1;
            break;
        }
        if (!mz_zip_writer_add_mem(&zip, name, fbuf, (size_t)fsize,
                                   MZ_DEFAULT_COMPRESSION)) {
            kprintf("zip: %s: cannot store\n", argv[i]);
            kfree(fbuf);
            fail = 1;
            break;
        }
        kfree(fbuf);
    }
    if (!fail && !mz_zip_writer_finalize_archive(&zip)) {
        vga_puts("zip: cannot finalize archive\n");
        fail = 1;
    }
    if (!fail && mz_zip_writer_mem_ptr(&zip)) {
        obuf = (unsigned char *)mz_zip_writer_mem_ptr(&zip);
        osize = (unsigned long)mz_zip_writer_mem_size(&zip);
        if (!obuf) fail = 1;
        else {
            f = kfopen(argv[1], "w");
            if (!f) { kprintf("zip: %s: cannot create\n", argv[1]); fail = 1; }
            else if (kfwrite(obuf, 1, osize, f) != osize || kfclose(f) != 0) {
                kprintf("zip: %s: write failed\n", argv[1]);
                fail = 1;
            } else {
                kprintf("zip: wrote %s (%lu bytes)\n", argv[1], osize);
            }
        }
    }
    mz_zip_writer_end(&zip);
    if (fail) kprintf("zip: %s: failed\n", argv[1]);
}