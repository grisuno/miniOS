#include "kernel.h"

/* ================================================================
 *  RAMDisk — flat file system in memory
 * ================================================================ */

#define RD_MAGIC       0x4B534452
#define RD_HEADER_SIZE 8
#define RD_ENTRY_SIZE  (RAMDISK_FNAME_LEN + 8)
#define RD_DATA_MIN    (512UL * 1024)
#define RD_DATA_SPARE  (1024UL * 1024)
#define RD_DATA_MAX    (48UL * 1024 * 1024)

typedef struct {
    unsigned magic;
    unsigned count;
    RDFile  files[RAMDISK_MAX_FILES];
} RDSuper;

static RDSuper *rd;
static char    *rd_data;
static unsigned rd_used;
static unsigned rd_cap;

static int ramdisk_reserve(unsigned long want) {
    if (want > RD_DATA_MAX) return 0;
    if (want < RD_DATA_MIN) want = RD_DATA_MIN;
    if (rd_data && rd_cap >= want) return 1;
    char *area = kmalloc(want);
    if (!area) {
        kprintf("ramdisk: cannot allocate %lu KB (heap exhausted)\n",
                want / 1024);
        return 0;
    }
    kmemset(area, 0, want);
    if (rd_data && rd_used > 0) kmemcpy(area, rd_data, rd_used);
    if (rd_data) kfree(rd_data);
    rd_data = area;
    rd_cap  = (unsigned)want;
    return 1;
}

void ramdisk_setup_from(void *data, unsigned size) {
    char *raw = (char *)data;
    unsigned i;

    if (!raw || size < RD_HEADER_SIZE) return;
    if (*(unsigned *)raw != RD_MAGIC) return;

    unsigned count = *(unsigned *)(raw + 4);
    if (count > RAMDISK_MAX_FILES) return;

    unsigned long table_bytes = (unsigned long)count * RD_ENTRY_SIZE;
    if (table_bytes > (unsigned long)size - RD_HEADER_SIZE) return;

    char *entry_start = raw + RD_HEADER_SIZE;
    char *data_start  = entry_start + table_bytes;
    unsigned long payload = (unsigned long)size - RD_HEADER_SIZE - table_bytes;

    unsigned long total = 0;
    for (i = 0; i < count; i++) {
        char *esrc = entry_start + (unsigned long)i * RD_ENTRY_SIZE;
        unsigned fsize = *(unsigned *)(esrc + RAMDISK_FNAME_LEN);
        unsigned forig = *(unsigned *)(esrc + RAMDISK_FNAME_LEN + 4);
        if (forig > payload || fsize > payload - forig) return;
        if (total > RD_DATA_MAX - fsize) return;
        total += fsize;
    }

    if (!rd) ramdisk_init();
    if (!rd) return;
    if (!ramdisk_reserve(total + RD_DATA_SPARE)) {
        kprintf("ramdisk: image needs %u bytes, capacity unavailable\n",
                (unsigned)total);
        return;
    }

    unsigned offset = 0;
    for (i = 0; i < count; i++) {
        char *esrc = entry_start + (unsigned long)i * RD_ENTRY_SIZE;
        unsigned fsize = *(unsigned *)(esrc + RAMDISK_FNAME_LEN);
        unsigned forig = *(unsigned *)(esrc + RAMDISK_FNAME_LEN + 4);
        RDFile *f = &rd->files[i];
        kmemcpy(f->name, esrc, RAMDISK_FNAME_LEN);
        f->name[RAMDISK_FNAME_LEN - 1] = 0;
        f->size   = fsize;
        f->offset = offset;
        if (fsize) kmemcpy(rd_data + offset, data_start + forig, fsize);
        offset += fsize;
    }
    rd->count = count;
    rd_used   = offset;
}

void ramdisk_init(void) {
    if (!rd) {
        rd = kcalloc(1, sizeof(RDSuper));
        if (!rd) return;
        rd_used = 0;
        rd_cap  = 0;
        rd_data = 0;
        if (!ramdisk_reserve(RD_DATA_MIN)) {
            kfree(rd);
            rd = 0;
            return;
        }
        rd->magic = RD_MAGIC;
        rd->count = 0;
    }
}

RDFile *ramdisk_open(const char *name) {
    unsigned i;
    if (!rd) return 0;
    for (i = 0; i < rd->count; i++) {
        if (kstrcmp(rd->files[i].name, name) == 0)
            return &rd->files[i];
    }
    return 0;
}

int ramdisk_read(RDFile *f, void *buf, unsigned offset, unsigned len) {
    if (!f || !buf || !rd_data) return 0;
    if (offset >= f->size) return 0;
    if (offset + len > f->size) len = f->size - offset;
    kmemcpy(buf, rd_data + f->offset + offset, len);
    return (int)len;
}

int ramdisk_write(RDFile *f, const void *buf, unsigned offset, unsigned len) {
    if (!f || !buf || !rd_data) return 0;
    if (offset >= f->size) return 0;
    if (offset + len > f->size) len = f->size - offset;
    kmemcpy(rd_data + f->offset + offset, buf, len);
    return (int)len;
}

RDFile *ramdisk_create(const char *name, unsigned size) {
    if (!rd || !name || rd->count >= RAMDISK_MAX_FILES) return 0;
    if (size > RD_DATA_MAX - rd_used) return 0;
    if (!ramdisk_reserve((unsigned long)rd_used + size)) return 0;
    RDFile *f = &rd->files[rd->count];
    kstrncpy(f->name, name, RAMDISK_FNAME_LEN - 1);
    f->name[RAMDISK_FNAME_LEN - 1] = 0;
    f->size   = size;
    f->offset = rd_used;
    rd_used  += size;
    rd->count++;
    return f;
}

int ramdisk_resize(RDFile *f, unsigned newsize) {
    unsigned i;
    if (!rd || !f || !rd_data) return 0;
    if (newsize == f->size) return 1;

    unsigned old_end = f->offset + f->size;
    unsigned new_end = f->offset + newsize;
    unsigned delta;
    unsigned move_len;

    if (newsize > f->size) {
        delta = newsize - f->size;
        if (delta > RD_DATA_MAX - rd_used) return 0;
        if (!ramdisk_reserve((unsigned long)rd_used + delta)) return 0;
        move_len = rd_used - old_end;
        for (i = 0; i < rd->count; i++)
            if (&rd->files[i] != f && rd->files[i].offset >= old_end)
                rd->files[i].offset += delta;
        kmemmove(rd_data + new_end, rd_data + old_end, move_len);
        kmemset(rd_data + old_end, 0, delta);
        f->size  = newsize;
        rd_used += delta;
        return 1;
    }

    delta    = f->size - newsize;
    move_len = rd_used - old_end;
    kmemmove(rd_data + new_end, rd_data + old_end, move_len);
    kmemset(rd_data + rd_used - delta, 0, delta);
    for (i = 0; i < rd->count; i++)
        if (&rd->files[i] != f && rd->files[i].offset >= old_end)
            rd->files[i].offset -= delta;
    f->size  = newsize;
    rd_used -= delta;
    return 1;
}

int ramdisk_list(RDFile **out, int max) {
    if (!rd) return 0;
    int n = (int)rd->count < max ? (int)rd->count : max;
    unsigned i;
    for (i = 0; i < (unsigned)n; i++) out[i] = &rd->files[i];
    return n;
}

int ramdisk_count(void) {
    if (!rd) return 0;
    return (int)rd->count;
}

const char *ramdisk_file_name(int idx) {
    if (!rd || (unsigned)idx >= rd->count) return "";
    return rd->files[idx].name;
}

int ramdisk_delete(RDFile *f) {
    unsigned i;
    int idx = -1;
    if (!rd || !f) return 0;
    for (i = 0; i < rd->count; i++) {
        if (&rd->files[i] == f) { idx = (int)i; break; }
    }
    if (idx < 0) return 0;

    unsigned old_end = f->offset + f->size;
    unsigned move_len = rd_used - old_end;
    kmemmove(rd_data + f->offset, rd_data + old_end, move_len);
    for (i = 0; i < rd->count; i++)
        if (&rd->files[i] != f && rd->files[i].offset >= old_end)
            rd->files[i].offset -= f->size;
    for (i = (unsigned)idx; i + 1 < rd->count; i++)
        rd->files[i] = rd->files[i + 1];
    rd->count--;
    rd_used -= f->size;
    return 1;
}
