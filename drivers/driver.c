#include "driver.h"

/* driver.c -- Device registry for the Strategy-pattern driver layer.
 *
 * Dependency-free by design (own string helpers, static table): the
 * registry is host-testable without the kernel (tests/test_driver.c,
 * `make test-driver`). Registration is boot-time only; dispatch only
 * reads, so no lock is needed. A null, nameless or full-table register
 * returns -1 and changes nothing; find on a missing name returns 0. */

static device_t dev_table[DEV_MAX];
static int dev_used;

static unsigned dev_len(const char *s) {
    unsigned n = 0;
    while (s[n]) n++;
    return n;
}

static void dev_copy(char *dst, const char *src, unsigned cap) {
    unsigned i = 0;
    if (!cap) return;
    while (i + 1 < cap && src[i]) { dst[i] = src[i]; i++; }
    dst[i] = 0;
}

static int dev_eq(const char *a, const char *b) {
    while (*a && *a == *b) { a++; b++; }
    return *a == *b;
}

void device_reset(void) {
    int i;
    for (i = 0; i < DEV_MAX; i++) {
        dev_table[i].name[0] = 0;
        dev_table[i].type = 0;
        dev_table[i].block = 0;
        dev_table[i].audio = 0;
        dev_table[i].priv = 0;
    }
    dev_used = 0;
}

int device_register(device_t *dev) {
    int i;
    if (!dev || !dev->name[0]) return -1;
    if (dev_len(dev->name) >= DEV_NAME_LEN) return -1;
    for (i = 0; i < DEV_MAX; i++) {
        if (dev_table[i].name[0] && dev_eq(dev_table[i].name, dev->name))
            return -1;
    }
    for (i = 0; i < DEV_MAX; i++) {
        if (!dev_table[i].name[0]) {
            dev_copy(dev_table[i].name, dev->name, DEV_NAME_LEN);
            dev_table[i].type = dev->type;
            dev_table[i].block = dev->block;
            dev_table[i].audio = dev->audio;
            dev_table[i].priv = dev->priv;
            dev_used++;
            return 0;
        }
    }
    return -1;
}

device_t *device_find(const char *name) {
    int i;
    if (!name) return 0;
    for (i = 0; i < DEV_MAX; i++) {
        if (dev_table[i].name[0] && dev_eq(dev_table[i].name, name))
            return &dev_table[i];
    }
    return 0;
}

device_t *device_find_by_type(int type) {
    int i;
    for (i = 0; i < DEV_MAX; i++) {
        if (dev_table[i].name[0] && dev_table[i].type == type)
            return &dev_table[i];
    }
    return 0;
}

int device_count(void) {
    return dev_used;
}
